#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/statfs.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

using namespace std;

void showFileSystem(char *filesyspath){
    struct statfs fsinfo;
    if(statfs(filesyspath,&fsinfo)!=0){
        perror("fstatfs");
        exit(-1);
    }

    printf("file system type: 0x%lx\n",fsinfo.f_type);
    printf("block size: %lu bytes\n",fsinfo.f_bsize);
    printf("total data blocks: %lu blocks\n",fsinfo.f_blocks);
}

int main(int argc,char *argv[]){
    if(argc<2){
        perror("args num error");
        exit(-1);
    }

    showFileSystem(argv[1]);
    return 0;
}