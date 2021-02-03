#include "updatercore.h"

typedef std::string String;
template <typename T>
using Vector=std::vector<T>;
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

size_t UpdaterCore::buffer_w(char* ptr,size_t size,size_t nmemb,void* stream){
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
size_t UpdaterCore::writer_curl(char* ptr,size_t size,size_t nmemb,void* stream){
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
QString UpdaterCore::get_json(){
    String json_url="https://fascodenet.github.io/serenelinux-update-info/update-lists.json";
    CURL *curl;
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,json_url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    UpdaterCore::curl_buffer *buf;
    buf=(UpdaterCore::curl_buffer*)malloc(sizeof(UpdaterCore::curl_buffer));
    buf->data=NULL;
    buf->size=0;
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, buf);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,UpdaterCore::buffer_w);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    QString json_data=buf->data;
    free(buf->data);
    free(buf);
    return json_data;
}
UpdaterCore::update_info UpdaterCore::get_update_info(){
    UpdaterCore::update_info infokun;
    QString jsonkun=get_json();
    QString current_ver=QString::fromStdString(check_current_ver());
    QByteArray bytearrayskun=jsonkun.toUtf8();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(bytearrayskun));
    QJsonObject jsonObj(jsonDoc.object());
    QJsonObject current_versionskun=jsonObj["current_versions"].toObject();
        QString last_ver=current_versionskun[current_ver].toObject()["latest_upg"].toString();
        for(QJsonValue verkun:current_versionskun[current_ver].toObject()["upgrade_ver"].toArray()){
            std::cout << QString::fromUtf8(QJsonDocument(verkun.toObject()).toJson()).toStdString() << std::endl;
            if(verkun.toObject()["ver"].toString() == last_ver){
                infokun.vername=QString(last_ver);
                infokun.description=QString(verkun["description"].toString());
                return infokun;
            }
        }
    return infokun;



}
