#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>

using namespace std;
#define DIRLEN 128

void traverse(const char *dirname){
    DIR *dir=opendir(dirname);
    if(dir==NULL){
        perror("open dir error");
        exit(-1);
    }
    dirent *child;
    while((child=readdir(dir))!=NULL){
        printf("filename: %s\tfiletype: %d\n",child->d_name,child->d_type);
    }
}

int main(int argc,char *argv[]){
    char dirname[DIRLEN]={0};
    if(getcwd(dirname,sizeof(dirname))==NULL){
        perror("get current path error");
        exit(-1);
    }
    if(argc==1){
        traverse(dirname);
    }else{
        if(argv[1][0]=='/'){
            traverse(argv[1]);
        }else{
            strcat(dirname,"/");
            strcat(dirname,argv[1]);
            traverse(dirname);
        }
    }
    return 0;
}