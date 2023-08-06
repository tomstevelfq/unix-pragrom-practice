//实现lsr
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

using namespace std;

bool lsr(char *path){
    struct stat st;
    if(stat(path,&st)!=0){
        perror("stat error");
        exit(-1);
    }

    if(S_ISDIR(st.st_mode)){
        cout<<path<<endl;
        DIR *dir=opendir(path);
        dirent *dirpath;
        bool flag=false;
        while((dirpath=readdir(dir))!=NULL){
            if(strcmp(dirpath->d_name,".")&&strcmp(dirpath->d_name,"..")){
                int pathlen=strlen(path);
                strcat(path,"/");
                strcat(path,dirpath->d_name);
                flag|=lsr(path);
                path[pathlen]='\0';
            }
        }
        if(flag){
            cout<<endl;
        }
        return false;
    }else{
        cout<<path<<"\t";
        return true;
    }
}

int main(int argc,char *argv[]){
    if(argc<2){
        perror("args num error");
        exit(-1);
    }

    lsr(argv[1]);
    return 0;
}