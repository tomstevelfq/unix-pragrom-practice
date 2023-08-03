#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

//根目录的上一级目录就是它自己

using namespace std;

ino_t get_inode(const char *dirname){
    struct stat st;
    if(stat(dirname,&st)!=0){
        perror("stat error");
        exit(-1);
    }
    return st.st_ino;
}

//文件节点转化成文件名称
void inode_to_name(ino_t inode,char *namebuf){
    DIR *dir=opendir(".");
    namebuf[0]='\0';
    dirent *file;
    while((file=readdir(dir))!=NULL){
        if(file->d_ino==inode){
            strcpy(namebuf,file->d_name);
            return;
        }
    }
    closedir(dir);
}

void pwd_print(ino_t inode){
    ino_t par=get_inode("..");
    if(par!=inode){
        chdir("..");
        char namebuf[128];
        inode_to_name(inode,namebuf);
        if(namebuf[0]!='\0'){
            pwd_print(par);
            printf("/%s",namebuf);
        }
    }else{
        return;
    }
}

void pwd(){
    ino_t inode=get_inode(".");
    pwd_print(inode);
    printf("\n");
}

int main(){
    pwd();
    return 0;
}