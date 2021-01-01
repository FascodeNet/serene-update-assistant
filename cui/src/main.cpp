#include <serene_updater.hpp>
#include <unistd.h>
#include <stdio.h>
int main(int argc,char* argv[]){
    int i,opt;
    opterr=0;
    bool isyes=false;
    bool istest=false;
    while((opt = getopt(argc,argv,"yt")) != -1){
        switch(opt){
            case 'y':
                isyes=true;
                break;
            case 't':
                istest=true;
                break;
            default:
                std::cout << "Usage " << argv[0] << "[-t] [-y] " << std::endl;
                break;
        }
    }
    String channel_name;
    if(istest){
        channel_name="release_testing";
    }else
    {
        channel_name="release";
    }
    
    serene_updater serene_updaterkun(channel_name);
    if(serene_updaterkun.isneed_update()){
        std::cout << "you need update" << std::endl;
    }else{
        std::cout << "no update" << std::endl;
        return 0;
    }
    
    if(!isyes){
        while(true){
            std::cout << "Update? [y/N]:" << std::flush;
            char c=getchar();
            if(c == 'y')
                break;
            return 0;
        }
    }
    serene_updaterkun.update();


}