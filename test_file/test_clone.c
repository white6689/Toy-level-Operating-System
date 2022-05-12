#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sched.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <signal.h>

#define STACK_SIZE 1024*64

int threadFunc(void* arg)
{
    //kill(getpid(), SIGKILL);

    int max=*((int*)arg);
    for(int i=0;i<max;i++){
        printf("%d: %d\n",getpid(), i);
    }
    return 0;
}

int main(){
    int pid;
    int status;
    int arg = 100;
    //int flags = SIGCHLD|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_VM;
    char* pStack ;
    pStack = (char*)malloc(STACK_SIZE);
    pid = clone(threadFunc,(char*)pStack+STACK_SIZE,SIGCHLD|CLONE_FS, &arg); // 초ㅑㅣㅇ
    wait(&status);
    printf("current pid, first clone: %d\n", getpid());
    printf("what is pid: %d\n", pid);
    arg = 200;
    pid = clone(threadFunc,(char*)pStack+STACK_SIZE*2,SIGCHLD|CLONE_FS, &arg); 
    printf("current pid, second clone: %d\n", getpid());
    printf("what is pid: %d\n", pid);
    
    int n=waitpid(pid, NULL, 0);
}
