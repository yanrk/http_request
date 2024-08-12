/********************************************************
 * Description : base
 * Author      : yanrk
 * Email       : yanrkchina@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2024
 ********************************************************/

#ifndef BASE_H
#define BASE_H


#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>

#ifndef __FILENAME__
    #define __FILENAME__ (strrchr("/" __FILE__, '/') + 1)
#endif // __FILENAME__

#define RUN_LOG_DBG(fmt, ...) run_log(__FILENAME__, __FUNCTION__, __LINE__, "[DBG] " fmt, ##__VA_ARGS__)
#define RUN_LOG_WAR(fmt, ...) run_log(__FILENAME__, __FUNCTION__, __LINE__, "[WAR] " fmt, ##__VA_ARGS__)
#define RUN_LOG_ERR(fmt, ...) run_log(__FILENAME__, __FUNCTION__, __LINE__, "[ERR] " fmt, ##__VA_ARGS__)

void run_log(const char * file, const char * func, int line, const char * format, ...);

uint64_t get_ns_time();
void sleep_ms(uint32_t ms);


#endif // BASE_H
