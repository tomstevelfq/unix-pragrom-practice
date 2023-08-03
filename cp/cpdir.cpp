//对整个文件夹进行拷贝
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<dirent.h>
#include<sys/stat.h>

using namespace std;
#define READ_LEN 100
char src[1024];
char dest[1024];

void cp(const char *file1,const char *file2){
    int fd=open(file1,O_RDONLY);
    if(fd==-1){
        perror("源文件");
        exit(-1);
    }

    // O_RDWR表示读写权限  O_TRUNC表示文件存在就将文件变成空文件 O_CREAT表示文件不存在就创建一个新文件
    int dst=open(file2,O_RDWR|O_TRUNC|O_CREAT,0644);
    if(dst==-1){
        perror("目的文件");
        printf("%s\n",file2);
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

void preproc(char *srcname,char *destname,char *src,char *dest){
    char cwd[128];
    if(getcwd(cwd,sizeof(cwd))==NULL){
        perror("get cwd");
        exit(-1);
    }
    strcat(cwd,"/");

    if(srcname[0]!='/'){
        strcpy(src,cwd);
    }
    if(destname[0]!='/'){
        strcpy(dest,cwd);
    }
    strcat(src,srcname);
    strcat(dest,destname);
}

void traverse(char *srcname,char *destname){
    struct stat filestat;
    int ret_stat=stat(srcname,&filestat);
    if(ret_stat==-1){
        perror("stat");
        exit(-1);
    }

    if(S_ISREG(filestat.st_mode)||S_ISLNK(filestat.st_mode)){
        //如果是文件类型直接复制
        cp(srcname,destname);
        return;
    }else if(S_ISDIR(filestat.st_mode)){
        //如果是文件夹类型就进行遍历
        //首先判断目标文件夹是否存在，不存在就创建
        if(access(destname,F_OK)!=0){
            if(mkdir(destname,0777)!=0){
                perror("create dir failed");
                exit(-1);
            }
        }
        DIR *dir=opendir(srcname);
        dirent *child=NULL;
        while((child=readdir(dir))!=NULL){
            strcpy(src,srcname);
            strcpy(dest,destname);
            if(strcmp(child->d_name,".")&&strcmp(child->d_name,"..")){
                strcat(src,"/");
                strcat(src,child->d_name);
                strcat(dest,"/");
                strcat(dest,child->d_name);
                traverse(src,dest);
            }
        }
        closedir(dir);
    }else{
        perror("file type error");
        exit(-1);
    }
}

int main(int argc,char *argv[]){
    if(argc<3){
        perror("参数数目错误");
        exit(-1);
    }

    char srcname[1024];
    char destname[1024];
    preproc(argv[1],argv[2],srcname,destname);//预处理统一转换成绝对路径
    traverse(srcname,destname);//拷贝整个文件夹
    return 0;
}