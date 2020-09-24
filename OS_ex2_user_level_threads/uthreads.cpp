#include "uthreads.h"
#include "ThreadDescriptor.h"
#include <cstdio>
#include <csetjmp>
#include <map>
#include <list>
#include <csignal>
#include <sys/time.h>
#include <algorithm>
#include <unistd.h>

static const char *const THREAD_LIBRARY_ERR = "thread library error:";
static const char *const SYSTEM_ERR = "system error:";

static struct sigaction sa{};

static int *priority_to_quantums;
static int total_quantums;

static std::map<unsigned int, ThreadDescriptor*> tcbs;

// data structures representing states of the threads
static std::list<ThreadDescriptor*> ready_threads;
static std::list<ThreadDescriptor*> blocked_threads;
static ThreadDescriptor* running_tcb;

static sigset_t signals_to_block_set;

static void print_thread_error(char* error_msg){
    fprintf(stderr,  "%s %s\n", THREAD_LIBRARY_ERR, error_msg);
    fflush(stderr);
}

static void handle_system_error(char* error_msg){
    fprintf(stderr,  "%s %s\n", SYSTEM_ERR, error_msg);
    fflush(stderr);
    exit(1);
}

static void safe_sigprocmask(int action) {
    if (sigprocmask(action, &signals_to_block_set, nullptr)) {
        handle_system_error((char*)"Masking signals didn't work");
    }
}

void context_switch(int sigNum) {
    safe_sigprocmask(SIG_BLOCK);

    // not terminate
    if (sigNum != SIGUSR2) {
        int ret_val = sigsetjmp(*running_tcb->get_env(), 0);
        if (ret_val == 1) {
            return;
        }
    }

    // regular case
    if (sigNum == SIGVTALRM) {
        ready_threads.push_back(running_tcb);
    }
    running_tcb = ready_threads.front();
    ready_threads.pop_front();

    running_tcb->inc_quantums();
    total_quantums += 1;

    struct itimerval timer{};

    // One time alarm for time mapped to next thread's priority
    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = priority_to_quantums[running_tcb->get_priority()];

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer (ITIMER_VIRTUAL, &timer, nullptr)) {
        handle_system_error((char*)"Setting timer didn't work");
    }

    safe_sigprocmask(SIG_UNBLOCK);
    siglongjmp(*running_tcb->get_env(),1);
}

int uthread_init(int *quantum_usecs, int size) {
    total_quantums = 1;
    if (sigaddset(&signals_to_block_set, SIGVTALRM)) {
        handle_system_error((char*)"Adding to signal set failed");
    }

    priority_to_quantums = new(std::nothrow) int[size];

    if (priority_to_quantums == nullptr) {
        handle_system_error((char *) "Memory allocation failed");
    }

    if (size < 1) {
        print_thread_error((char *) "Size must be positive");
        return -1;
    }

    for (int i=0; i<size; ++i) {
        if (quantum_usecs[i] < 0 || quantum_usecs[i] > 999999) {
            print_thread_error((char *) "Quantum time must be between 0 and 999999");
            return -1;
        }
        priority_to_quantums[i] = quantum_usecs[i];
    }

    auto main_thread = new(std::nothrow) ThreadDescriptor(nullptr, 0, 0);
    if (main_thread == nullptr) {
        handle_system_error((char *) "Memory allocation failed");
    }
    tcbs.insert({0, main_thread});
    running_tcb = main_thread;
    running_tcb->inc_quantums();

    sa.sa_handler = &context_switch;

    if (sigaction(SIGVTALRM, &sa, nullptr) < 0) {
        handle_system_error((char *)"Sigaction didn't work");
    }

    struct itimerval timer{};

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = priority_to_quantums[running_tcb->get_priority()];

    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;

    if (setitimer (ITIMER_VIRTUAL, &timer, nullptr)) {
        handle_system_error((char*)"Setting timer didn't work");
    }

    return 0;
}

int uthread_spawn(void (*f)(), int priority) {
    if (tcbs.size() == MAX_THREAD_NUM) {
        print_thread_error((char*)"maximal thread size reached");
        return -1;
    }

    for (int i=0; i<MAX_THREAD_NUM; ++i) {
        if (tcbs.find(i) == tcbs.end()) {
            safe_sigprocmask(SIG_BLOCK);
            auto new_thread = new(std::nothrow) ThreadDescriptor(f, i, priority);
            if (new_thread == nullptr) {
                handle_system_error((char *) "Memory allocation failed");
            }
            else {
                tcbs.insert({i, new_thread});
                // adding the new thread to the ready list
                ready_threads.push_back(new_thread);
                safe_sigprocmask(SIG_UNBLOCK);
                return i;
            }
        }
    }

    return -1;
}

int uthread_change_priority(int tid, int priority)
{
    auto tcb_pair = tcbs.find(tid);

    if(tcb_pair == tcbs.end()){
        print_thread_error((char*)"thread not found");
        return -1;
    }

    tcb_pair->second->set_priority(priority);
    return 0;
}

int uthread_terminate(int tid){
  auto tcb_pair = tcbs.find(tid);
  if (tcb_pair == tcbs.end()) {
      print_thread_error((char *)"tid not found");
      return -1;
  }

  if (tid == 0) {
      safe_sigprocmask(SIG_BLOCK);
      for(auto &tcb : tcbs) {
          delete tcb.second;
      }
      safe_sigprocmask(SIG_UNBLOCK);
      exit(0);
  }
  else if (running_tcb->get_tid() == tid) {
      safe_sigprocmask(SIG_BLOCK);
      delete tcbs.find(tid)->second;
      tcbs.erase(tid);
      safe_sigprocmask(SIG_UNBLOCK);
      context_switch(SIGUSR2);
  }
  else {
      auto ready_itr = std::find(ready_threads.begin(), ready_threads.end(), tcb_pair->second);
      auto blocked_itr = std::find(blocked_threads.begin(), blocked_threads.end(), tcb_pair->second);

      safe_sigprocmask(SIG_BLOCK);
      if (ready_itr != ready_threads.end()) {
          ready_threads.erase(ready_itr);
      }
      else if (blocked_itr != ready_threads.end()) {
          blocked_threads.erase(blocked_itr);
      }
      delete tcbs.find(tid)->second;
      tcbs.erase(tid);
      safe_sigprocmask(SIG_UNBLOCK);

      return 0;
  }

  for (;;) {
  }
}

int uthread_block(int tid) {
    auto tcb_pair = tcbs.find(tid);
    if (tcb_pair == tcbs.end()) {
        print_thread_error((char *)"tid not found");
        return -1;
    }

    if (tid == 0) {
        print_thread_error((char *)"main thread cannot be blocked");
        return -1;
    }

    auto ready_search = find(ready_threads.begin(), ready_threads.end(), tcb_pair->second);
    if (ready_search != ready_threads.end()) {
        safe_sigprocmask(SIG_BLOCK);
        blocked_threads.push_back(*ready_search);
        ready_threads.erase(ready_search);
        safe_sigprocmask(SIG_UNBLOCK);
    }
    else if (uthread_get_tid() == tid) {
        safe_sigprocmask(SIG_BLOCK);
        blocked_threads.push_back(running_tcb);
        safe_sigprocmask(SIG_UNBLOCK);
        context_switch(SIGUSR1);
    }

    return 0;
}

int uthread_get_tid() {
    return running_tcb->get_tid();
}

int uthread_resume(int tid) {
    auto tcb_pair = tcbs.find(tid);
    if (tcb_pair == tcbs.end()) {
        print_thread_error((char *)"tid not found");
        return -1;
    }

    auto blocked_search = find(blocked_threads.begin(), blocked_threads.end(), tcb_pair->second);
    if (blocked_search != blocked_threads.end()) {
        safe_sigprocmask(SIG_BLOCK);
        ready_threads.push_back(*blocked_search);
        blocked_threads.erase(blocked_search);
        safe_sigprocmask(SIG_UNBLOCK);
    }

    return  0;
}

int uthread_get_total_quantums() {
    return total_quantums;
}

int uthread_get_quantums(int tid) {
    auto tcb_pair = tcbs.find(tid);
    if (tcb_pair == tcbs.end()) {
        print_thread_error((char *)"tid not found");
        return -1;
    }

    return tcb_pair->second->get_quantums();
}
