#include<iostream>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

using namespace std;

int getsplit(char *src){
    for(int i=strlen(src)-1;i>=0;i--){
        if(src[i]=='/'){
            return i+1;
        }
    }
    return 0;
}

void mv(char *src,char *dest){
    struct stat dest_st;
    if(stat(dest,&dest_st)!=0 && S_ISDIR(dest_st.st_mode)){
        sprintf(dest,"%s/%s",dest,src+getsplit(src));
        rename(src,dest);
    }else{
        rename(src,dest);
    }
}

int main(int argc,char *argv[]){
    if(argc<3){
        perror("args num error");
        exit(-1);
    }

    mv(argv[1],argv[2]);
    return 0;
}