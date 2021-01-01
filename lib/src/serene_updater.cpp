#include "serene_updater.hpp"
serene_updater::serene_updater(String current_upd_channel){
    current_channel=current_upd_channel;
    current_version=get_current_version();
}
size_t serene_updater_name::buffer_w(char* ptr,size_t size,size_t nmemb,void* stream){
    curl_buffer * buf=(curl_buffer*)stream;
    int block=size * nmemb;
    if(!buf){
        return block;
    }
    if(!buf->data){
        buf->data=(char*)malloc(block);
    }
    else{
        buf->data=(char*)realloc(buf->data,buf->size+block);
    }
    if(buf->data){
        memcpy(buf->data+buf->size,ptr,block);
        buf->size += block;
    }
    return block;
}
bool serene_updater::isneed_update(){
    int current=atoi(current_version.c_str());
    String download_url="https://repo.dyama.net/new_serene_updater/latest_" + current_channel;
    CURL *curl;
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,download_url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    serene_updater_name::curl_buffer *buf;
    buf=(serene_updater_name::curl_buffer*)malloc(sizeof(serene_updater_name::curl_buffer));
    buf->data=NULL;
    buf->size=0;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,serene_updater_name::buffer_w);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    String new_ver=String(buf->data);
    free(buf->data);
    free(buf);
    int new_v=atoi(new_ver.c_str());
    return current < new_v;

}
String serene_updater::get_current_version(){
    String os_release="/etc/os-release";
    std::ifstream osr(os_release);
    if(osr.fail()){
        std::cerr << "Failed!" << std::endl;
        exit(-1);
    }
    String linekun;
    String search_str="VERSION_ID";
    while(getline(osr,linekun)){
        String replaced_str=std::regex_replace(linekun,std::regex(" "),"");
        if(replaced_str.size() >= search_str.size() && std::equal(std::begin(search_str),std::end(search_str),std::begin(replaced_str))) {
            return std::regex_replace(replaced_str,std::regex(search_str + "="),"");
        }
    }
    return "FAILED!";
}