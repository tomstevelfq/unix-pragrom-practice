#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void orphan(){
    printf("this is child process %d,my father is %d\n",getpid(),getppid());
    sleep(3);
    printf("this is child process %d,my father is %d\n",getpid(),getppid());
    sleep(1);
}

void parent(){
    printf("this is parent process %d\n",getpid());
    sleep(1);
}

int main(){
    int pid;
    if((pid=fork())==0){
        orphan();
    }else{
        parent();
    }
    return 0;
}