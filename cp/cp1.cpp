//改进版本的cp程序，使用自定义的缓冲区
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

using namespace std;

#define BUFFLEN 10
#define READLEN 3

struct buffer{
    char data[BUFFLEN];
    int curpos;
    int len;
    int fd;
};

void initBuff(const char *fileName,buffer &buff){
    int fd=open(fileName,O_RDONLY);
    if(fd==-1){
        perror("open file error");
        exit(-1);
    }
    buff.fd=fd;
    buff.len=0;
    buff.curpos=0;
}

bool reloadBuff(buffer &buff){
    buff.len=read(buff.fd,buff.data,BUFFLEN);
    if(buff.len==-1){
        perror("buffreload");
        exit(-1);
    }else if(buff.len==0){
        return false;
    }
    buff.curpos=0;
    return true;
}

bool hasNext(const buffer &buff){
    return buff.curpos<buff.len;
}

void readLen(buffer &buff,int &len,char *dest){
    int reserveLen=buff.len-buff.curpos;
    len=reserveLen<len?reserveLen:len;
    memcpy(dest,buff.data+buff.curpos,len);
    buff.curpos=buff.curpos+len;
}

int main(int argc,char *argv[]){
    if(argc<3){
        perror("参数长度不够");
        exit(-1);
    }

    buffer buff;

    initBuff(argv[1],buff);
    char dest[READLEN];
    
    int fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
    int realLen=READLEN;
    while(true){
        if(hasNext(buff)){
            readLen(buff,realLen,dest);
            int wrlen=write(fd,dest,realLen);
            if(wrlen!=realLen){
                perror("wrtie error");
                exit(-1);
            }
        }else if(!reloadBuff(buff)){
            close(fd);
            break;
        }
    }

    return 0;
}