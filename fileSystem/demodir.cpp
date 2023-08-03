//创建一个demodir目录
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>

using namespace std;
#define READ_LEN 100

void copy(const char *filename1,const char *filename2){
    int fd=open(filename1,O_RDWR);
    if(fd==-1){
        perror("源文件");
        exit(-1);
    }

    // O_RDWR表示读写权限  O_TRUNC表示文件存在就将文件变成空文件 O_CREAT表示文件不存在就创建一个新文件
    int dst=open(filename2,O_RDWR|O_TRUNC|O_CREAT,0644);
    if(dst==-1){
        perror("目的文件");
        exit(-1);
    }
    char buff[READ_LEN];
    int len;
    while((len=read(fd,buff,READ_LEN))>0){
        if(write(dst,buff,len)!=len){
            perror("write error");
            exit(-1);
        }
    }
    if(close(fd)==-1||close(dst)==-1){
        perror("close");
    }
}

void demodir(){
    int ret=mkdir("demodir",0777);
    if(ret!=0){
        perror("文件夹创建错误");
        exit(-1);
    }
    if(chdir("demodir")!=0){
        perror("文件夹切换错误");
        exit(-1);
    }

    ret=mkdir("a",0777);
    if(ret!=0){
        perror("文件夹创建错误");
        exit(-1);
    }

    if(chdir("a")!=0){
        perror("文件夹切换错误");
        exit(-1);
    }

    FILE *file=fopen("x","w+");
    if(file==NULL){
        perror("file open error");
        exit(-1);
    }
    fprintf(file,"%s\n","hello this is 一个文件");
    fclose(file);

    if(chdir("..")!=0){
        perror("文件夹切换错误");
        exit(-1);
    }

    ret=mkdir("c",0777);
    if(ret!=0){
        perror("文件夹创建错误");
        exit(-1);
    }

    if(chdir("c")!=0){
        perror("文件夹切换错误");
        exit(-1);
    }

    if(link("../a/x","xlink")!=0){
        perror("链接错误");
        exit(-1);
    }

    copy("../a/x","xcopy");
    return;
}

int main(){
    demodir();
    return 0;
}