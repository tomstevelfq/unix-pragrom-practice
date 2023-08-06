//显示目录中文件的i节点号
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>

using namespace std;

void showinode(char *path){

}

int main(int argc,char *argv[]){
    if(argc<2){
        perror("args num");
        exit(-1);
    }

    struct stat st;
    if(stat(argv[1],&st)!=0){
        perror("stat error");
        exit(-1);
    }

    cout<<st.st_ino<<endl;
    return 0;
}