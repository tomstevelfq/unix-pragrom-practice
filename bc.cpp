#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<signal.h>
#include<sys/types.h>

using namespace std;

int main(){
	char expr[256];
	char *arg[]={"dc","-e","3 45 + p",NULL};
	scanf("%s",expr);
	if(execv("/usr/bin/dc",arg)==-1){
		perror("dc error");
	}
	int result=kill(getpid(),SIGINT);
	if(result==0){
		printf("signal send success\n");
	}else{
		perror("signal send error");
	}
	return 0;
}
