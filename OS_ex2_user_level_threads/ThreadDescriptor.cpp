//
// Created by Matan on 15/04/2020.
//

#include "ThreadDescriptor.h"
#include "uthreads.h"
#include <csetjmp>

#ifdef __x86_64__
/* code for 64 bit Intel arch */

typedef unsigned long address_t;
#define JB_SP 6
#define JB_PC 7

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%fs:0x30,%0\n"
                 "rol    $0x11,%0\n"
    : "=g" (ret)
    : "0" (addr));
    return ret;
}

#else
/* code for 32 bit Intel arch */

typedef unsigned int address_t;
#define JB_SP 4
#define JB_PC 5

/* A translation is required when using an address of a variable.
   Use this as a black box in your code. */
address_t translate_address(address_t addr)
{
    address_t ret;
    asm volatile("xor    %%gs:0x18,%0\n"
		"rol    $0x9,%0\n"
                 : "=g" (ret)
                 : "0" (addr));
    return ret;
}

#endif

static const char *const SYSTEM_ERR = "system error: ";

static void handle_system_error(char* error_msg){
    fprintf(stderr,  "%s %s\n", SYSTEM_ERR, error_msg);
    fflush(stderr);
    exit(1);
}

ThreadDescriptor::ThreadDescriptor(void (*f)(), int tid, int priority) {
    _priority = priority;
    _tid = tid;
    sigsetjmp(_env, 0);
    address_t sp, pc;
    _quantums = 0;

    _stack = new(std::nothrow) char[STACK_SIZE];
    if (_stack == nullptr) {
        handle_system_error((char *) "Memory allocation failed");
    }

    sp = (address_t)_stack + STACK_SIZE - sizeof(address_t);
    pc = (address_t)f;

    (_env->__jmpbuf)[JB_SP] = translate_address(sp);
    (_env->__jmpbuf)[JB_PC] = translate_address(pc);
}

ThreadDescriptor::~ThreadDescriptor() {
    delete[] _stack;
}

void ThreadDescriptor::set_priority(int priority) {
    _priority = priority;
}

int ThreadDescriptor::get_priority() const {
    return _priority;
}

void ThreadDescriptor::inc_quantums() {
    ++_quantums;
}

int ThreadDescriptor::get_quantums() const {
    return _quantums;
}

sigjmp_buf* ThreadDescriptor::get_env() {
    return &_env;
}

int ThreadDescriptor::get_tid() const {
    return _tid;
}
