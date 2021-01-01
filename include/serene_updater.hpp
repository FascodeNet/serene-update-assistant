#pragma once
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <iostream>
#include <curl/curl.h>
typedef std::string String;
template <typename T>
using Vector=std::vector<T>;
namespace serene_updater_name{
    struct curl_buffer{
        char* data;
        int size;
    };
    size_t buffer_w(char* ptr,size_t size,size_t nmemb,void* stream);
}
class serene_updater{
    private:
        String current_channel;
        String current_version;
        String next_version;
        String get_current_version();
    public:
        serene_updater(String current_upd_channel);
        bool isneed_update();
};