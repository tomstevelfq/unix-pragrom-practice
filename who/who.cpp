#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<unistd.h>
#include<fcntl.h>
#include<time.h>

#define BUFFLEN 400
char tembuff[BUFFLEN];//用户级缓冲区
int offset=0;//缓冲区指针偏移
int tailoffset=0;
int fd;

//缓冲区空重载，需要把尾部数据拷贝到前面
//重新载入文件数据后足够一个结构体返回true，不够返回false
bool reloadBuff(){
    if(tailoffset==BUFFLEN){
        int newoffset=0;
        while(offset<BUFFLEN){
            *(tembuff+newoffset++)=*(tembuff+offset++);
        }
        offset=0;
        tailoffset=newoffset;
    }
    int len;
    if((len=read(fd,tembuff+tailoffset,BUFFLEN-tailoffset))>0){
        tailoffset+=len;
    }
    if(tailoffset-offset<sizeof(utmp)){
        return false;
    }else{
        return true;
    }
}

bool hasnext(){
    //缓冲区不够一个结构体且重载后依然不足够一个结构体就返回false
    if(tailoffset-offset<sizeof(utmp)&&!reloadBuff()){
        return false;
    }else{
        return true;
    }
}

int main(int argc,char *argv[]){
    printf("%d\n",sizeof(utmp));
    //需要设置read函数为非阻塞
    fd=open("/var/run/utmp",O_RDWR|O_NONBLOCK);
    if(fd==-1){
        perror(argv[0]);
        exit(-1);
    }
    struct utmp u={0};
    int len=sizeof(utmp);
    while(hasnext()){
        struct utmp *u=(struct utmp*)(tembuff+offset);
        time_t t=u->ut_time;
        printf("username: %s\nhostname: %s\ntty: %s\ntime: %stype: %d\n\n",u->ut_user,u->ut_host,u->ut_line,ctime(&t)+4,u->ut_type);
        offset+=sizeof(utmp);
    }
    close(fd);
    return 0;
}