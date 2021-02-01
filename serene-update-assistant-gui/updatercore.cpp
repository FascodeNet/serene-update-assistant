#include "updatercore.h"

UpdaterCore::UpdaterCore()
{

}
std::string UpdaterCore::check_current_ver(){
    std::ifstream current_ver_file("/etc/serenelinux-release");
    if(!current_ver_file.is_open()){
        return "33.0.0";
    }else{
        current_ver_file.close();
        std::ifstream current_ver_file2("/etc/serenelinux-release",std::ios::in);
        std::string current_v;
        current_ver_file2 >> current_v;
        current_ver_file2.close();
        return std::regex_replace(std::regex_replace(current_v,std::regex("\n"),""),std::regex("\r"),"");
    }
}
