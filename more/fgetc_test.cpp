#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include<utmp.h>

int main(int argc,char *argv[]){
    struct utmp *u;
    utmpname("/var/run/utmp");
    while((u=getutent())!=NULL){
        printf("%s\n",u->ut_user);
        printf("%s\n\n",u->ut_host);
    }
    return 0;
}