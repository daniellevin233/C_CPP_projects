#include <cassert>
#include "VirtualMemory.h"
#include "PhysicalMemory.h"

struct TraversalStruct {
    bool emptyTable;
    uint64_t tableFrame;
    uint64_t maxFrameNum;
    word_t fatherEntryAddr;
    uint64_t curPageIdx;
    uint64_t storedPagesNums[NUM_FRAMES][3];
};

void translate(uint64_t virtualAddress, uint64_t &currTableFrame);

uint64_t unsignedSubtract(uint64_t a, uint64_t b) {
    return (a>b) ? a-b : b-a;
}

void clearTable(uint64_t frameIndex) {
    for (uint64_t i = 0; i < PAGE_SIZE; ++i) {
        PMwrite(frameIndex * PAGE_SIZE + i, 0);
    }
}

void VMinitialize() {
    clearTable(0);
}

// 1000 getBitsInRange(3,0)
uint64_t getBitsInRange(uint64_t address, uint64_t i, uint64_t j) {
    address = address >> j;
    uint64_t mask = (1LL << (i-j+1)) - 1; // 00001 -> 100000 -> 011111
    return address & mask;
}

void getTraversal(word_t addr, int depth, TraversalStruct& traversalData, word_t parentEntryAddr, uint64_t curPath,
        uint64_t replacingPageNum) {
    traversalData.maxFrameNum = (addr / PAGE_SIZE > traversalData.maxFrameNum) ?
                                addr / PAGE_SIZE : traversalData.maxFrameNum;
    if (depth == TABLES_DEPTH) {
        traversalData.storedPagesNums[traversalData.curPageIdx][0] = curPath;
        traversalData.storedPagesNums[traversalData.curPageIdx][1] = addr / PAGE_SIZE;
        traversalData.storedPagesNums[traversalData.curPageIdx][2] = parentEntryAddr;
        ++traversalData.curPageIdx;
        return;
    }

    bool isEmpty = true;
    // Same virtual tree prefix or root node
    bool isParent = depth == 0 || getBitsInRange(replacingPageNum,
            CEIL((double)VIRTUAL_ADDRESS_WIDTH/OFFSET_WIDTH)*OFFSET_WIDTH-OFFSET_WIDTH-1,
            CEIL((double)VIRTUAL_ADDRESS_WIDTH/OFFSET_WIDTH)*OFFSET_WIDTH-OFFSET_WIDTH*(1+depth)) == curPath;

    word_t val;
    for (int i=0; i<PAGE_SIZE; ++i) {
        PMread(addr + i, &val);
        if (val != 0) {
            isEmpty = false;

            curPath <<= OFFSET_WIDTH;
            getTraversal(val * PAGE_SIZE, depth + 1, traversalData, addr + i,
                    curPath + i, replacingPageNum);
            curPath >>= OFFSET_WIDTH;
        }
    }

    if (isEmpty && !isParent) {
        traversalData.emptyTable = true;
        traversalData.tableFrame = addr / PAGE_SIZE;
        traversalData.fatherEntryAddr = parentEntryAddr;
    }
}

void translate(uint64_t virtualAddress, uint64_t &currTableFrame) {
    uint64_t currIdx = CEIL((double)VIRTUAL_ADDRESS_WIDTH/OFFSET_WIDTH)*OFFSET_WIDTH;
    uint64_t soughtPageNum = getBitsInRange(virtualAddress,
                                          VIRTUAL_ADDRESS_WIDTH-1,
                                          OFFSET_WIDTH);
    word_t memoryVal;

    for (int i=0; i<TABLES_DEPTH; i+=1) {
        uint64_t stageOffset = getBitsInRange(virtualAddress, currIdx - 1, currIdx - OFFSET_WIDTH);
        PMread(currTableFrame * PAGE_SIZE + stageOffset, &memoryVal);
        // If still reading pointer to table
        if (memoryVal == 0) {
            TraversalStruct dfsTraversal = {false, 0, 0,
                                            0, 0,{{0}}};
            getTraversal(0, 0, dfsTraversal, 0, 0, soughtPageNum);
            uint64_t frameToUse;
            if(dfsTraversal.emptyTable){
                frameToUse = dfsTraversal.tableFrame;
                PMwrite(dfsTraversal.fatherEntryAddr, 0);
            } else {
                if(dfsTraversal.maxFrameNum < NUM_FRAMES - 1){
                    frameToUse = dfsTraversal.maxFrameNum + 1;
                } else {
                    // max{min{NUM_PAGES-|page_swapped_in-p|, |page_swapped_in-p|}}
                    uint64_t furthestPageNum = NUM_PAGES;
                    // Always bigger - evicting page different than the one inserted
                    uint64_t maxCyclicDistance = 0;
                    uint64_t furthestStoredPageIdx = 0;
                    for (uint64_t idx=0;idx<dfsTraversal.curPageIdx;++idx) {
                        uint64_t pageNum = dfsTraversal.storedPagesNums[idx][0];
                        uint64_t distanceFromStart = unsignedSubtract(soughtPageNum, pageNum);
                        uint64_t distanceFromEnd = NUM_PAGES - distanceFromStart;
                        uint64_t pageCyclicDistance =
                                distanceFromStart<distanceFromEnd ? distanceFromStart : distanceFromEnd;
                        if (pageCyclicDistance > maxCyclicDistance) {
                            maxCyclicDistance = pageCyclicDistance;
                            furthestPageNum = pageNum;
                            furthestStoredPageIdx = idx;
                        }
                    }

                    frameToUse = dfsTraversal.storedPagesNums[furthestStoredPageIdx][1];
                    PMevict(frameToUse, furthestPageNum);
                    PMwrite(dfsTraversal.storedPagesNums[furthestStoredPageIdx][2], 0);
                }
            }

            memoryVal = frameToUse;
            // if pointing to table
            if (i < (TABLES_DEPTH-1)) {
                clearTable(frameToUse);
            } else {
                PMrestore(frameToUse, soughtPageNum);
            }
            PMwrite(currTableFrame * PAGE_SIZE + stageOffset, memoryVal);
        }
        currIdx = currIdx - OFFSET_WIDTH;
        currTableFrame = memoryVal;
    }
}

int VMread(uint64_t virtualAddress, word_t* value) {
    if (virtualAddress >= VIRTUAL_MEMORY_SIZE) {
        return 0;
    }
    uint64_t tableFrame = 0;
    translate(virtualAddress, tableFrame);
    PMread(tableFrame * PAGE_SIZE + getBitsInRange(virtualAddress, OFFSET_WIDTH-1, 0), value);
    return 1;
}


int VMwrite(uint64_t virtualAddress, word_t value) {
    if (virtualAddress >= VIRTUAL_MEMORY_SIZE) {
        return 0;
    }
    uint64_t tableFrame = 0;
    translate(virtualAddress, tableFrame);
    PMwrite(tableFrame * PAGE_SIZE + getBitsInRange(virtualAddress, OFFSET_WIDTH-1, 0), value);
    return 1;
}
