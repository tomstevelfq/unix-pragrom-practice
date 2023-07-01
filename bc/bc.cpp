#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstring>

using namespace std;

void rundc(){
	char *arg[]={"dc","-e","3 45 + p",NULL};
	if(execv("/usr/bin/dc",arg)==-1){
		perror("dc error");
	}
	return;
}

void child(){
	printf("this is child\n");
	return;
}

int main(){
	char expr[256];
	int pid;
	if((pid=fork())==0){
		printf("this is son process\n");
		rundc();//run dc process
	}else{
		printf("this is father process\n");
		//wait for child proc to finish
		char buff[256];
		//pid=wait(NULL);
		printf("child process %d end\n",pid);
	}
	return 0;
}
