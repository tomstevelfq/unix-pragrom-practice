#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
using namespace std;

// support three types of data
enum DataType{
    Integer,
    String,
    Double
};

FILE *Fopen(const char *filename,const char *mode){
    FILE *file=fopen(filename,mode);
    if(file==NULL){
        perror("open file error");
        exit(-1);
    }
    return file;
}

void writeInner(FILE *file,DataType type,void *data){
    switch(type){
        case Integer:
            fprintf(file,"%d",*(int*)data);
            break;
        case String:
            fprintf(file,"%s",(char*)data);
            break;
        case Double:
            fprintf(file,"%f",*(double*)data);
            break;
        default:
            perror("unsupport type");
            exit(-1);
            break;
    }
    return;
}

void write(const char *filename,DataType type,void *data){
    FILE *file=Fopen(filename,"w");
    writeInner(file,type,data);
}

void writeAppend(const char *filename,DataType type,void *data){
    FILE *file=Fopen(filename,"a");
    writeInner(file,type,data);
}

int main(){
    // test sample
    int data1=34;
    write("haah.txt",Integer,&data1);
    writeAppend("t.txt",String,(char*)"this is hello\n");
    printf("test end\n");
    return 0;
}