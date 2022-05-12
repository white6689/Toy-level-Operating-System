#include<stdio.h>
#include<unistd.h>

int main(){
    __pid_t pid;
    pid=fork();
    if(pid>0)//부모 프로세스라면
        printf("부모 프로세스 %d\n", getpid());
    else if(pid==0){//자식 프로세스라면
        printf("자식 프로세스 %d\n", getpid());
        pid=fork();//자식이 손자 프로세스를 생성
        if(pid>0)//자식 프로세스라면
            printf("자식 프로세스 %d\n", getpid());
        else
            printf("자손 프로세스 %d\n", getpid());
    }
    else   
        printf("에러\n");

    return 0;
}