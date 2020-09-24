#include "MapReduceClient.h"
#include "MapReduceFramework.h"
#include <vector>
#include <atomic>
#include <map>
#include <cmath>
#include <iostream>
#include <bitset>

struct JobContext {
    std::atomic<uint64_t> atomicState;
    std::map<pthread_t, int> threadToID;

    const MapReduceClient& client;
    const InputVec& inputVec;

    OutputVec& outputVec;
    pthread_mutex_t outputVecMutex;

    std::vector<pthread_mutex_t> mapStageMutexes;
    std::vector<std::vector<IntermediatePair>> mapStageOutputs;
    IntermediateMap intermediateMap;
    std::vector<K2*> intermediateMapSortedKeys;

    std::atomic<size_t> totalShuffleCtr;
    std::atomic<size_t> inputVecCtr;
    std::atomic<int> mapThreadRunningCtr;
    std::atomic<size_t> intermediateMapCtr;
    std::atomic<size_t> shuffledCtr;

    pthread_cond_t shuffleFinished;
};

void handleSystemError(const std::string& msg) {
    std::cerr << "system error: " << msg << std::endl;
    exit(1);
}

void getJobState(JobHandle job, JobState* state) {
    /*
     * StateBinary variable is of the format bits #0-1 - stage
     *                                            #2-32 - total job in stage
     *                                            #33-63 - total progress in stage
     */
    auto jobContext = (JobContext*)job;
    uint64_t stateBinary = jobContext->atomicState;
    stage_t stage = static_cast<stage_t>(stateBinary & 3);

    uint64_t binaryLength = (((uint64_t)1 << 31) - 1);
    uint64_t maskProgress = binaryLength << 33;
    uint64_t maskTotal = binaryLength << 2;
    uint64_t progress = (stateBinary & maskProgress) >> 33;
    uint64_t total = (stateBinary & maskTotal) >> 2;

    float percentage;
    if (total == 0) {
        percentage = 0;
    } else {
        percentage = ((float)progress / total) * 100;
    }

    state->stage = stage;
    state->percentage = percentage;
}

void updateState(JobHandle job, stage_t stage) {
    auto jobContext = (JobContext *)job;
    uint64_t stateBinary = 0;

    uint64_t stateProgress, stateTotalJob;
    uint64_t zeroAnd31Ones = ((uint64_t)1 << 31) - 1;
    if (stage == MAP_STAGE){
        stateProgress = 0;
        stateTotalJob = jobContext->inputVec.size() & zeroAnd31Ones;
    } else if (stage == SHUFFLE_STAGE){
        stateProgress = jobContext->shuffledCtr & zeroAnd31Ones;
        stateTotalJob = jobContext->totalShuffleCtr;
    } else if (stage == REDUCE_STAGE){
        stateProgress = 0;
        stateTotalJob = jobContext->intermediateMapSortedKeys.size() & zeroAnd31Ones;
    } else {
        stateProgress = 0;
        stateTotalJob = 0;
    }

    stateBinary += stateProgress << 33;
    stateBinary += stateTotalJob << 2;
    stateBinary += stage;
    jobContext->atomicState = stateBinary;
}

void emit2 (K2* key, V2* value, void* context) {
    auto jobContext = (JobContext *)context;
    ++jobContext->totalShuffleCtr;

    pthread_mutex_lock(&(jobContext->mapStageMutexes[jobContext->threadToID[pthread_self()]]));
    jobContext->mapStageOutputs[jobContext->threadToID[pthread_self()]].push_back(IntermediatePair(key, value));
    pthread_mutex_unlock(&jobContext->mapStageMutexes[jobContext->threadToID[pthread_self()]]);
}

void emit3 (K3* key, V3* value, void* context) {
    auto jobContext = (JobContext *)context;
    pthread_mutex_lock(&jobContext->outputVecMutex);
    jobContext->outputVec.push_back(OutputPair(key, value));
    pthread_mutex_unlock(&jobContext->outputVecMutex);
}

void runReduce(JobContext* job) {
    while(job->intermediateMapCtr < job->intermediateMapSortedKeys.size()) {
        int old_index = job->intermediateMapCtr++;

        job->client.reduce(job->intermediateMapSortedKeys[old_index],
                           job->intermediateMap[job->intermediateMapSortedKeys[old_index]], job);
        job->atomicState.fetch_add((uint64_t)1 << 33);
    }
}

void* runMap(JobHandle job) {
    auto jobContext = (JobContext*)job;
    const int threadID = jobContext->threadToID[pthread_self()];
    while (jobContext->inputVecCtr < jobContext->inputVec.size()) {
        int old_index = jobContext->inputVecCtr++;

        jobContext->client.map(jobContext->inputVec[old_index].first,
                               jobContext->inputVec[old_index].second, jobContext);
        jobContext->atomicState.fetch_add((uint64_t)1 << 33);
    }

    --jobContext->mapThreadRunningCtr;
    pthread_cond_wait(&jobContext->shuffleFinished, &jobContext->mapStageMutexes[threadID]);//wait for reduce

    runReduce(jobContext);

    return job;
}

void shuffleKeys(JobContext *jobContext) {
    for (size_t i=0; i < jobContext->mapStageOutputs.size(); ++i) {
        pthread_mutex_lock(&jobContext->mapStageMutexes[i]);
        for (auto &pair : jobContext->mapStageOutputs[i]) {
            ++jobContext->shuffledCtr;
            jobContext->intermediateMap[pair.first].push_back(pair.second);
            if ((jobContext->atomicState & 3) == SHUFFLE_STAGE) {
                jobContext->atomicState.fetch_add((uint64_t)1 << 33);
            }
        }
        jobContext->mapStageOutputs[i].clear();
        pthread_mutex_unlock(&jobContext->mapStageMutexes[i]);
    }
}

void* runShuffle(JobHandle job) {
    auto* jobContext = (JobContext*)job;

    while (jobContext->mapThreadRunningCtr > 0) {
        shuffleKeys(jobContext);
    }

    updateState(job, SHUFFLE_STAGE);
    shuffleKeys(jobContext);

    for (const auto& pair : jobContext->intermediateMap) {
        jobContext->intermediateMapSortedKeys.push_back(pair.first);
    }

    jobContext->intermediateMapCtr = 0;

    updateState(job, REDUCE_STAGE);
    pthread_cond_broadcast(&jobContext->shuffleFinished); //start reduce
    runReduce(jobContext);

    return job;
}

JobHandle startMapReduceJob(const MapReduceClient& client,
                            const InputVec& inputVec, OutputVec& outputVec,
                            int multiThreadLevel) {

    auto jobContext = new(std::nothrow) JobContext{.client = client, .inputVec = inputVec, .outputVec = outputVec,
                                     .outputVecMutex = PTHREAD_MUTEX_INITIALIZER,
            .mapStageMutexes = {(unsigned long)multiThreadLevel-1, PTHREAD_MUTEX_INITIALIZER},
            .mapStageOutputs = {(unsigned long)multiThreadLevel-1, std::vector<IntermediatePair>()},
                                     .shuffleFinished = PTHREAD_COND_INITIALIZER};
    if (!jobContext) {
        handleSystemError("Memory allocation failed");
    }

    int ctr = 0;
    for (int i=0; i<multiThreadLevel-1; ++i) {
        jobContext->mapStageMutexes.push_back(PTHREAD_MUTEX_INITIALIZER);
        ++ctr;
    }
    jobContext->mapThreadRunningCtr = multiThreadLevel - 1;

    int mapThreadIDCtr = 0;
    jobContext->totalShuffleCtr = 0;

    updateState((JobHandle) jobContext, MAP_STAGE);
    for (int i=0; i<multiThreadLevel-1; ++i) {
        int mapThreadID = mapThreadIDCtr++;
        pthread_t mapThread;
        if (pthread_create(&mapThread, nullptr, runMap, jobContext) != 0) {
            handleSystemError("couldn't create thread");
        }
        jobContext->threadToID[mapThread] = mapThreadID;
    }

    pthread_t shuffleThread;
    if (pthread_create(&shuffleThread, nullptr, runShuffle, jobContext) != 0) {
        handleSystemError("couldn't create thread");
    }

    return (JobHandle)jobContext;
}

void waitForJob(JobHandle job){
    auto jobContext = (JobContext*) job;

    JobState state;
    getJobState(job, &state);

    for (auto& threadPair : jobContext->threadToID) {
        pthread_join(threadPair.first, nullptr);
    }
}

void closeJobHandle(JobHandle job){
    waitForJob(job);
    auto jobContext = (JobContext*) job;

    for (auto& mutex: jobContext->mapStageMutexes){
        if (pthread_mutex_destroy(&mutex) != 0) {
            handleSystemError("couldn't destroy mutex");
        }
    }

    if (pthread_cond_destroy(&jobContext->shuffleFinished) != 0) {
        handleSystemError("couldn't destroy cond");
    }

    if (pthread_mutex_destroy(&jobContext->outputVecMutex) != 0) {
        handleSystemError("couldn't destroy mutex");
    }
    delete jobContext;
}
