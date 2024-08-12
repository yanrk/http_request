/********************************************************
 * Description : http manager
 * Author      : yanrk
 * Email       : yanrkchina@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2024
 ********************************************************/

#ifndef HTTP_MANAGER_H
#define HTTP_MANAGER_H


#include <map>
#include <string>
#include <functional>
#include "singleton.hpp"
#include "task_actuator.hpp"

class HttpManager
{
public:
    HttpManager();
    ~HttpManager();

public:
    void get(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & headers, const std::function<void(bool result, const std::string & response)> & callback);
    void post(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & headers, const std::string & request, const std::function<void(bool result, const std::string & response)> & callback);

private:
    HttpManager(const HttpManager &) = delete;
    HttpManager(HttpManager &&) = delete;
    HttpManager & operator = (const HttpManager &) = delete;
    HttpManager & operator = (HttpManager &&) = delete;

private:
    friend class Singleton<HttpManager>;

private:
    TaskActuator                        m_task_actuator;
};


#endif // HTTP_MANAGER_H
