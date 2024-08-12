/********************************************************
 * Description : http client
 * Author      : yanrk
 * Email       : yanrkchina@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2024
 ********************************************************/

#include "http_client.h"
#include "http_manager.h"

void HttpClient::get(const std::string & host, const std::string & uri, const std::function<void(bool result, const std::string & response)> & callback)
{
    std::multimap<std::string, std::string> headers;
    Singleton<HttpManager>::instance().get(host, uri, headers, callback);
}

void HttpClient::get(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & headers, const std::function<void(bool result, const std::string & response)> & callback)
{
    Singleton<HttpManager>::instance().get(host, uri, headers, callback);
}

void HttpClient::post(const std::string & host, const std::string & uri, const std::function<void(bool result, const std::string & response)> & callback)
{
    std::multimap<std::string, std::string> headers;
    std::string request;
    Singleton<HttpManager>::instance().post(host, uri, headers, request, callback);
}

void HttpClient::post(const std::string & host, const std::string & uri, const std::string & request, const std::function<void(bool result, const std::string & response)> & callback)
{
    std::multimap<std::string, std::string> headers;
    Singleton<HttpManager>::instance().post(host, uri, headers, request, callback);
}

void HttpClient::post(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & headers, const std::string & request, const std::function<void(bool result, const std::string & response)> & callback)
{
    Singleton<HttpManager>::instance().post(host, uri, headers, request, callback);
}
