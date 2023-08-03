//这个程序实现了ls -l的功能
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/stat.h>
#include<pwd.h>
#include<grp.h>
#include<time.h>
#include<vector>

using namespace std;

struct fileinfo{
    char permis[11];
    int linknum;
    char username[128];
    char groupname[128];
    int size;
    char date[128];
    char filename[128];
};

void getPermis(char *permis,struct stat &file_info){
    permis[0]=S_ISDIR(file_info.st_mode) ? 'd' : '-';
    permis[1]=(file_info.st_mode & S_IRUSR) ? 'r' : '-';
    permis[2]=(file_info.st_mode & S_IWUSR) ? 'w' : '-';
    permis[3]=(file_info.st_mode & S_IXUSR) ? 'x' : '-';
    permis[4]=(file_info.st_mode & S_IRGRP) ? 'r' : '-';
    permis[5]=(file_info.st_mode & S_IWGRP) ? 'w' : '-';
    permis[6]=(file_info.st_mode & S_IXGRP) ? 'x' : '-';
    permis[7]=(file_info.st_mode & S_IROTH) ? 'r' : '-';
    permis[8]=(file_info.st_mode & S_IWOTH) ? 'w' : '-';
    permis[9]=(file_info.st_mode & S_IXOTH) ? 'x' : '-';
}

void getLinkNum(int &linkNum,struct stat &file_info){
    linkNum=file_info.st_nlink;
}

void getUserName(char *userName,struct stat &file_info){
    struct passwd *user_info=getpwuid(file_info.st_uid);
    if(user_info!=NULL){
        strcat(userName,user_info->pw_name);
    }
}

void getGroupName(char *groupName,struct stat &file_info){
    struct group *group_info=getgrgid(file_info.st_gid);
    if(group_info!=NULL){
        strcat(groupName,group_info->gr_name);
    }
}

void getFileSize(int &size,struct stat &file_info){
    size=file_info.st_size;
}

void getFileDate(char *date,struct stat &file_info){
    strcat(date,ctime(&file_info.st_mtime));
    date[strlen(date)-1]='\0';
}

void showFileInfo(fileinfo &finfo){
    printf("%s %d %s %s %d %s %s\n",finfo.permis,finfo.linknum,finfo.username,finfo.groupname,finfo.size,finfo.date,finfo.filename);
}

void getFileInfo(fileinfo &finfo,struct stat &file_stat){
    getPermis(finfo.permis,file_stat);
    getLinkNum(finfo.linknum,file_stat);
    getUserName(finfo.username,file_stat);
    getGroupName(finfo.groupname,file_stat);
    getFileSize(finfo.size,file_stat);
    getFileDate(finfo.date,file_stat);
}

void visit(char *dirname){
    struct stat filestat;
    if(stat(dirname,&filestat)!=0){
        perror("stat error");
        exit(-1);
    }
    if(S_ISDIR(filestat.st_mode)){
        DIR *dir=opendir(dirname);
        if(dir==NULL){
            perror("文件错误");
            exit(-1);
        }
        dirent *file=NULL;
        char permis[11]={0};
        char filename[1024];
        int totalSize=0;
        vector<fileinfo> fvec;
        while((file=readdir(dir))!=NULL){
            fileinfo finfo;
            memset(&finfo,0,sizeof(finfo));
            strcat(finfo.filename,file->d_name);
            if(strcmp(file->d_name,".")&&strcmp(file->d_name,"..")){
                strcpy(filename,dirname);
                strcat(filename,"/");
                strcat(filename,file->d_name);
                struct stat file_info;
                if(stat(filename,&file_info)!=0){
                    perror("stat error");
                    exit(-1);
                }
                getFileInfo(finfo,file_info);
                totalSize+=finfo.size;
                fvec.push_back(finfo);
            }
        }

        printf("totalSize: %dK\n",totalSize/1024);
        for(auto it:fvec){
            showFileInfo(it);
        }
    }else if(S_ISREG(filestat.st_mode)||S_ISLNK(filestat.st_mode)){
        fileinfo finfo;
        memset(&finfo,0,sizeof(finfo));
        char *slash=strrchr(dirname,'/');
        char *filename;
        if(slash==NULL){
            filename=dirname;
        }else{
            filename=slash+1;
        }
        strcpy(finfo.filename,filename);
        getFileInfo(finfo,filestat);
        showFileInfo(finfo);
    }
}

int main(int argc,char *argv[]){
    if(argc==1){
        char dirname[1024];
        if(getcwd(dirname,sizeof(dirname))==NULL){
            perror("get current dir error");
            exit(-1);
        }
        visit(dirname);
    }else if(argc==2){
        visit(argv[1]);
    }
    return 0;
}