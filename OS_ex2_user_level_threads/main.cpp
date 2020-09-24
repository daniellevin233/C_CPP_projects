//
// Created by Matan on 15/04/2020.
//
#include "uthreads.h"
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <csignal>

int quantum_to_usecs[] = {100000, 10000, 1000, 100};

void f() {
//    while (1) {
//        printf("f");
//        fflush(stdout);
//        pause();
//    }
    printf("f");
    uthread_terminate(uthread_get_tid());
}

void g() {
//    while (1) {
//        printf("g");
//        fflush(stdout);
//        pause();
//    }
    printf("g");
    uthread_terminate(uthread_get_tid());
}

int main() {
    uthread_init(quantum_to_usecs, 4);
    uthread_spawn(f, 3);
    uthread_spawn(g, 3);

    struct timeval interval = {0, 0};
    struct timeval val = {0, 100};
    struct itimerval timer = {interval ,val};

    if (setitimer (ITIMER_VIRTUAL, &timer, nullptr)) {
        printf("setitimer error.");
    }

    for(;;) {
        printf("main");
    }

    return 0;
}