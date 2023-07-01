#include<iostream>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
using namespace std;

void fun(){
	printf("%d\n",getpid());
	while(1){
		sleep(10);
	}
	return;
}

void fa(){
	while(1){
   		sleep(10);
   	}
	return;
}

int main(){
	printf("%d\n",getpid());
	if(fork()==0){
		fun();
	}else{
	   fa();	
	}
    	return 0;
}
