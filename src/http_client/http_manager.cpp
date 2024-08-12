/********************************************************
 * Description : http manager
 * Author      : yanrk
 * Email       : yanrkchina@163.com
 * Blog        : blog.csdn.net/cxxmaker
 * Version     : 1.0
 * Copyright(C): 2024
 ********************************************************/

#include "task_actuator.hpp"
#include "httplib.h"
#include "http_manager.h"
#include "base.h"

static time_t s_http_timeout = 3;

static bool http_get_request(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & request_headers, std::string & response_data)
{
    std::string url(host + uri);
    httplib::Client client(host);

    client.set_connection_timeout(s_http_timeout);
    client.set_read_timeout(s_http_timeout);
    client.set_write_timeout(s_http_timeout);
#ifndef _MSC_VER
    client.enable_server_certificate_verification(false);
#endif // _MSC_VER

    try
    {
        httplib::Headers headers(request_headers.begin(), request_headers.end());
        httplib::Result result = client.Get(uri, headers);
        if (result && 2 == result->status / 100)
        {
            response_data.swap(result->body);
            return true;
        }
        else
        {
            std::string err(result ? httplib::to_string(result.error()) : "send failure");
            RUN_LOG_ERR("http get request (%s) error: %s", url.c_str(), err.c_str());
            return false;
        }
    }
    catch (const std::exception & e)
    {
        RUN_LOG_ERR("http get request (%s) exception: %s", url.c_str(), e.what());
        return false;
    }
    catch (...)
    {
        RUN_LOG_ERR("http get request (%s) exception: unknown", url.c_str());
        return false;
    }
}

static bool http_post_request(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & request_headers, const std::string & request_data, std::string & response_data)
{
    std::string url(host + uri);
    httplib::Client client(host);

    client.set_connection_timeout(s_http_timeout);
    client.set_read_timeout(s_http_timeout);
    client.set_write_timeout(s_http_timeout);
#ifndef _MSC_VER
    client.enable_server_certificate_verification(false);
#endif // _MSC_VER

    try
    {
        httplib::Headers headers(request_headers.begin(), request_headers.end());
        httplib::Result result = client.Post(uri, headers, request_data, "application/json");
        if (result && 2 == result->status / 100)
        {
            response_data.swap(result->body);
            return true;
        }
        else
        {
            std::string err(result ? httplib::to_string(result.error()) : "send failure");
            RUN_LOG_ERR("http post request (%s) error: %s", url.c_str(), err.c_str());
            return false;
        }
    }
    catch (const std::exception & e)
    {
        RUN_LOG_ERR("http post request (%s) exception: %s", url.c_str(), e.what());
        return false;
    }
    catch (...)
    {
        RUN_LOG_ERR("http post request (%s) exception: unknown", url.c_str());
        return false;
    }
}

static bool http_upload_request(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & request_headers, const std::multimap<std::string, std::string> & request_forms, const std::string & src_file_path, const std::string & dst_file_name)
{
    std::string url(host + uri);
    httplib::Client client(host);

    client.set_connection_timeout(s_http_timeout);
    client.set_read_timeout(s_http_timeout);
    client.set_write_timeout(s_http_timeout);
#ifndef _MSC_VER
    client.enable_server_certificate_verification(false);
#endif // _MSC_VER

    try
    {
        httplib::Headers headers(request_headers.begin(), request_headers.end());

        std::ifstream file(src_file_path, std::ios::binary);
        std::stringstream buffer;
        buffer << file.rdbuf();

        httplib::MultipartFormDataItems items = { { dst_file_name, buffer.str(), src_file_path, "multipart/form-data" } };
        for (std::multimap<std::string, std::string>::const_iterator iter = request_forms.begin(); request_forms.end() != iter; ++iter)
        {
            httplib::MultipartFormData form_data = { iter->first, iter->second };
            items.emplace_back(std::move(form_data));
        }

        httplib::Result result = client.Post(uri, headers, items);
        if (result && 2 == result->status / 100)
        {
            return true;
        }
        else
        {
            std::string err(result ? httplib::to_string(result.error()) : "send failure");
            RUN_LOG_ERR("http upload (%s) request (%s) error: %s", src_file_path.c_str(), url.c_str(), err.c_str());
            return false;
        }
    }
    catch (const std::exception & e)
    {
        RUN_LOG_ERR("http upload (%s) request (%s) exception: %s", src_file_path.c_str(), url.c_str(), e.what());
        return false;
    }
    catch (...)
    {
        RUN_LOG_ERR("http upload (%s) request (%s) exception: unknown", src_file_path.c_str(), url.c_str());
        return false;
    }
}

HttpManager::HttpManager()
    : m_task_actuator(2)
{

}

HttpManager::~HttpManager()
{

}

void HttpManager::get(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & headers, const std::function<void(bool result, const std::string & response)> & callback)
{
    m_task_actuator.async_exec([=]{
        std::string response;
        bool result = http_get_request(host, uri, headers, response);
        callback(result, response);
    });
}

void HttpManager::post(const std::string & host, const std::string & uri, const std::multimap<std::string, std::string> & headers, const std::string & request, const std::function<void(bool result, const std::string & response)> & callback)
{
    m_task_actuator.async_exec([=]{
        std::string response;
        bool result = http_post_request(host, uri, headers, request, response);
        callback(result, response);
    });
}
