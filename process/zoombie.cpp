#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(){
    int pid;
    if(pid=fork()==0){
        printf("child process id is %d\n",getpid());
        sleep(1);
        printf("child end\n");
        exit(0);
    }else{
        printf("parent process id is %d\n",getpid());
        //先前对僵尸进程理解不到位的地方是，这里的父进程要休眠一个较长的时间，这时候子进程已经被终结但是父进程还没有来得及调用wait函数回收它，所以就多了一个僵尸进程占据着位置
        //如果父进程结束了，它的子进程已经结束的会被自动干掉
        //是不是父进程可以注册一个信号回调函数，当子进程结束信号发过来的时候，就自动调用wait函数回收
        //这是一种可以避免产生僵尸进程的机制
        sleep(200);
        wait(NULL);
        printf("parent end\n");
    }
    return 0;
}