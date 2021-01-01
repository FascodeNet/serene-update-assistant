#pragma once
#include <string>
#include <vector>
typedef std::string String;
template <typename T>
using Vector=std::vector<T>;
class serene_updater{
    private:
        String current_channel;
    public:
        serene_updater(String current_upd_channel);
};