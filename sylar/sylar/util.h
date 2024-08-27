#pragma once

#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/syscall.h>
#include<stdio.h>
#include<stdint.h>

namespace sylar
{
    pid_t GetThreadId() { return syscall(SYS_gettid);}
    uint32_t GetFiberId() { return 0;}
} // namespace sylar
