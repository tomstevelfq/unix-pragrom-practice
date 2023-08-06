//mkdir增强版本
//支持 -m和-p
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<vector>
#include<sstream>
#include<string.h>
#include<sys/stat.h>

using namespace std;

void getdirs(vector<string>& dirs,const char *path){
    stringstream ss;
    ss<<path;
    string item;
    while(getline(ss,item,'/')){
        dirs.push_back(item);
    }
}

void createDir(vector<string>& dirs,mode_t mode){
    if(dirs[0]==""){
        if(chdir("/")!=0){
            perror("chdir root");
            exit(-1);
        }
    }
    struct stat st;
    for(auto it:dirs){
        if(!(stat(it.c_str(),&st)==0&&S_ISDIR(st.st_mode))){
            mkdir(it.c_str(),mode);
            if(chdir(it.c_str())!=0){
                perror("chdir error");
                exit(-1);
            }
        }
    }
}

int main(int argc,char *argv[]){
    int opt;
    mode_t mode=0777;
    cout<<mode<<endl;
    bool pflag=false;
    char path[1024];
    while((opt=getopt(argc,argv,"m:p:"))!=-1){
        switch(opt){
            case 'm':
            {
                cout<<"选项:m\t"<<"参数"<<optarg<<endl;
                char *str;
                mode=strtol(optarg,&str,8);
                cout<<mode<<endl;
                break;
            }
            case 'p':
            {
                cout<<"选项:p\t"<<"参数"<<optarg<<endl;
                pflag=true;
                strcpy(path,optarg);
                break;
            }
            default:
            {
                perror("args error");
                exit(-1);
            }
        }
    }

    vector<string> dirs;
    if(pflag){
        getdirs(dirs,path);
        createDir(dirs,mode);
    }else{
        string dir(argv[optind]);
        dirs.push_back(dir);
        createDir(dirs,mode);
    }
    return 0;
}