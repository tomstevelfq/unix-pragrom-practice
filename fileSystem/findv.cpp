#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

using namespace std;

int getsplit(char *str){
    for(int i=strlen(str)-1;i>=0;i--){
        if(str[i]=='/'){
            return i+1;
        }
    }
    return 0;
}

void findv(char *path,char *filename){
    if(chdir(path)!=0){
        perror("chdir error");
        exit(-1);
    }

    struct stat st;
    if(stat(path,&st)!=0){
        perror("stat error");
        exit(-1);
    }

    if(S_ISDIR(st.st_mode)){

    }else{
        path=path+getsplit(path);
        if(strcmp(filename,path)==0){
            cout<<path<<endl;
        }
    }
}

int main(int argc,char *argv[]){
    if(argc<2){
        findv(".");
    }else{
        findv(argv[1]);
    }
    return 0;
}