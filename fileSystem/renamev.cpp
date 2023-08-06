#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

void renamev(char *src,char *dest){
    if(link(src,dest)!=0){
        perror("link error");
        exit(-1);
    }

    if(unlink(src)!=0){
        perror("unlink error");
        exit(-1);
    }

    return;
}

int main(int argc,char *argv[]){
    if(argc<3){
        perror("args num error");
        exit(-1);
    }

    renamev(argv[1],argv[2]);
    return 0;
}