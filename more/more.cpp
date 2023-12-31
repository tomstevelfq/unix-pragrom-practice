#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <termios.h>

using namespace std;
const int LINE_NUM=10;//每页显示10行
const char footer[]="\033[7m more? \033[m";

void displayFooter(){
    printf(footer);
}

int getopt(){
    FILE *file=fopen("/dev/tty","r");
    if(file==NULL){
        perror("file open error");
        exit(-1);
    }
    char opt;
    while((opt=fgetc(file))!=EOF){
        if(opt==' '){
            return 0;
        }else if(opt=='\n'){
            return LINE_NUM-1;
        }else if(opt=='q'){
            printf("get q\n");
            return -1;
        }
    }
    fclose(file);
    return LINE_NUM;
}

int main(int argc,char *argv[]){
    printf("%d\n",sizeof(footer));
    FILE *file;

    if(argc<2){
        file=stdin;
    }else{
        file=fopen(argv[1],"r");
    }

    if(file==NULL){
        perror("file open error");
        exit(-1);
    }

    int line_cnt=0;
    char str[100];
    while(line_cnt>=0){
        if(line_cnt<LINE_NUM){
            line_cnt++;
            if(fgets(str,sizeof(str),file)==NULL){
                break;//文件到头
            }
            printf("%s\n",str);
        }else{
            displayFooter();//显示下方状态条
            line_cnt=getopt();
        }
    }
    printf("end\n");
    return 0;
}
