#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
#include<time.h>

void recycle(int sid){
    int pid=wait(NULL);
    printf("child process %d is already recycled\n",pid);
    return;
}

int main(){
    clock_t start=clock();
    int pid;
    if(pid=fork()==0){
        printf("child process id is %d\n",getpid());
        sleep(1);
        printf("child end\n");
        exit(0);
    }else{
        printf("parent process id is %d\n",getpid());
        signal(SIGCHLD,recycle);
        //sleep一旦被中断就不能再继续sleep，所以可以用一个while循环
        int timeRemain=6;//sleep 6秒
        //这样，这个sleep函数即使被中断也可以继续睡眠
        while(timeRemain>0){
            timeRemain=sleep(timeRemain);
        }
        if(wait(NULL)==-1){
            perror("no child process needs to wait for");
        }
        printf("parent end\n");
    }
    clock_t end1=clock();
    sleep(2);
    clock_t end2=clock();
    printf("execute for %f seconds\n",(double) (end1 - start)/ CLOCKS_PER_SEC);
    printf("execute for %f seconds\n",(double) (end2 - end1));
    printf("%ld\n",CLOCKS_PER_SEC);
    return 0;
}