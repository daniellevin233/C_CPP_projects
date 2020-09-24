//
// Created by Matan on 15/04/2020.
//

#ifndef EX2_THREADDESCRIPTOR_H
#define EX2_THREADDESCRIPTOR_H

#include <csetjmp>
#include <string>

class ThreadDescriptor {
public:
    ThreadDescriptor(void (*f)(), int tid, int priority);
    ~ThreadDescriptor();

    void set_priority(int priority);
    int get_priority() const;

    void inc_quantums();
    int get_quantums() const;

    int get_tid() const;

    sigjmp_buf* get_env();
private:
    int _tid;
    int _priority;
    char* _stack;
    sigjmp_buf _env{};
    int _quantums;
};


#endif //EX2_THREADDESCRIPTOR_H
