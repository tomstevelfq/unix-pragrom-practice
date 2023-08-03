#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

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

int main(int argc,char *argv[]){
    if(argc<2){
        perror("参数不够");
        exit(-1);
    }
    copy(argv[1],argv[2]);
    return 0;
}