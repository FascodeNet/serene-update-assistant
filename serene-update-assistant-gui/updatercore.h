#ifndef UPDATERCORE_H
#define UPDATERCORE_H

#include <string>
#include<fstream>
#include <regex>
#include<iostream>
#include <QString>
#include <curl/curl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextEdit>
#include "ansiescapecodehandler.h"
#include "rep_IPC_Serene_source.h"
#define SERENE_PATH "/usr/bin/serene-update-assistant-gui"
class UpdaterCore
{
public:
    UpdaterCore();

    struct curl_buffer{
        char* data;
        int size;
    };
    struct update_info{
        QString vername;
        QString description;
        QString download_update_url;
    };
    QString app_file_path;
    static size_t buffer_w(char* ptr,size_t size,size_t nmemb,void* stream);
    static size_t writer_curl(char* ptr,size_t size,size_t nmemb,void* stream);
    std::string check_current_ver();
    update_info get_update_info();
    QString get_json();
    bool update(update_info* upinfo,QTextEdit* log_textedit);
    bool update_admin(update_info* upinfo);
private:
    typedef QList<Utils::FormattedText> FormattedTextList;
};

#endif // UPDATERCORE_H
