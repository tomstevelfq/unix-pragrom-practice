#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>

using namespace std;

void childhandler(int sid){
    printf("child接收到信号%d\n",sid);
    return;
}

void parenthandler(int sid){
    printf("parent接收到信号%d\n",sid);
    return;
}

void child(){
    //子进程注册一个信号
    signal(SIGINT,childhandler);
    while(1){
        sleep(1);
    }
}

void parent(){
    // 父进程注册一个信号
    signal(SIGINT,parenthandler);
    int cnt=0;
    while(cnt++<5){
        sleep(1);
    }
}

int main(){
    int pid;
    if((pid=fork())==0){
        printf("this is child process %d\n",getpid());
        child();
    }else{
        printf("this is parent process %d\n",getpid());
        parent();
        // 父进程终结时候要干掉子进程
        int result=kill(pid,SIGKILL);
        if(result==0){
            printf("信号发送成功\n");
        }else{
            perror("信号发送失败\n");
            exit(-1);
        }
        pid=wait(NULL);
        printf("已经回收子进程%d\n",pid);
    }
    return 0;
}