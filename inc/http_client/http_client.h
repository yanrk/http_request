/********************************************************
 * Description : http client
 * Author      : yanrk
 * Email       : yanrkchina@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2024
 ********************************************************/

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H


#include <map>
#include <string>
#include <functional>

class HttpClient
{
public:
    void get(const std::string & host, const std::string & uri, const std::function<void(bool result, const std::string & response)> & callback);
    void get(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & headers, const std::function<void(bool result, const std::string & response)> & callback);
    void post(const std::string & host, const std::string & uri, const std::function<void(bool result, const std::string & response)> & callback);
    void post(const std::string & host, const std::string & uri, const std::string & request, const std::function<void(bool result, const std::string & response)> & callback);
    void post(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & headers, const std::string & request, const std::function<void(bool result, const std::string & response)> & callback);
};


#endif // HTTP_CLIENT_H
