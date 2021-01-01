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
size_t serene_updater_name::writer_curl(char* ptr,size_t size,size_t nmemb,void* stream){
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
    String nnext_version=buf->data;
    next_version=std::regex_replace(nnext_version,std::regex("\n"),"");
    free(buf->data);
    free(buf);
    int new_v=atoi(next_version.c_str());
    newv=new_v;
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
int serene_updater::update(){
    std::cout << "Updating " << std::endl;
    String download_sh_url="https://repo.dyama.net/new_serene_updater/updater/" + std::to_string(newv);
    //String download_sh_url="https://repo.dyama.net/new_serene_updater/latest_release";
    std::cout << download_sh_url << std::endl;
    CURL *curl2;
    curl2=curl_easy_init();
    curl_easy_setopt(curl2,CURLOPT_URL,download_sh_url.c_str());
    curl_easy_setopt(curl2, CURLOPT_SSL_VERIFYPEER, 0);
    char tmp_kun[]="/tmp/serene_updateXXXXXX";
    int download_file_f=mkstemp(tmp_kun);
    String tmp_file_path="/proc/" + std::to_string(getpid()) + "/fd/" + std::to_string(download_file_f) ;
    std::ofstream out_streamkun(tmp_file_path,std::ios::out | std::ios::binary);
    umask(022);
    serene_updater_name::curl_buffer *buf;
    buf=(serene_updater_name::curl_buffer*)malloc(sizeof(serene_updater_name::curl_buffer));
    buf->data=NULL;
    buf->size=0;
    curl_easy_setopt(curl2, CURLOPT_WRITEDATA, buf);
    curl_easy_setopt(curl2, CURLOPT_WRITEFUNCTION,serene_updater_name::buffer_w);
    curl_easy_perform(curl2);
    curl_easy_cleanup(curl2);
    out_streamkun.write(buf->data,buf->size);
    out_streamkun.flush();
    free(buf->data);
    free(buf);
    //std::cout << execl(tmp_file_path.c_str(),tmp_file_path.c_str())  << std::endl;
    out_streamkun.close();
    close(download_file_f);
    umask(000);
    chmod(tmp_kun,0777);
    int child;
    int status;
    if((child=fork()) < 0){
        std::cerr << "fork err" << std::endl;
        unlink(tmp_kun);
        return -8;
    }
    if(child == 0 ){
        execl(tmp_kun,tmp_kun,NULL);
    }else{
        if(wait(&status) < 0){
            std::cerr << "wait" << std::endl;
            unlink(tmp_kun);
            return -7;
        }
    };
    unlink(tmp_kun);
    return 0;
}