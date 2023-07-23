#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
    int fd=open("test.txt",O_RDONLY);
    if(fd==-1){
        perror("open file arroe");
        exit(-1);
    }
    int fd1=open("test.txt",O_WRONLY);
    if(fd1==-1){
        perror("open file1 error");
        exit(-1);
    }
    int fd2=open("test.txt",O_RDWR);
    if(fd2==-1){
        perror("open file2 error");
        exit(-1);
    }

    int len=10;
    char buffer[len];
    FILE *file=fopen("/dev/tty","w");
    if(file==NULL){
        perror("file null");
        exit(-1);
    }
    int readlen;
    while((readlen=read(fd,buffer,len))>0){
        int count=fwrite(buffer,1,readlen,file);
        if(count!=readlen){
            perror("fwrite");
            exit(-1);
        }
    }
    close(fd);
    close(fd1);
    close(fd2);
    fclose(file);
    return 0;
}