/********************************************************
 * Description : base
 * Author      : yanrk
 * Email       : yanrkchina@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2024
 ********************************************************/

#include <unistd.h>
#include <ctime>
#include <cstdarg>
#include "base.h"

uint64_t get_ns_time()
{
    struct timespec time = {0, 0};
    clock_gettime(CLOCK_MONOTONIC, &time);
    return static_cast<uint64_t>(time.tv_sec) * 1000000000 + static_cast<uint64_t>(time.tv_nsec);
}

void sleep_ms(uint32_t ms)
{
    usleep(1000 * ms);
}

void run_log(const char * file, const char * func, int line, const char * format, ...)
{
    char buffer[1024] = { 0x0 };
    size_t size = 0;
#ifndef DEBUG
    size = snprintf(buffer, sizeof(buffer) - 1, "%s:%s:%d | ", file, func, line);
#endif // DEBUG
    va_list args;
    va_start(args, format);
    vsnprintf(buffer + size, sizeof(buffer) - 1 - size, format, args);
    va_end(args);
    printf("%s\n", buffer);
}
