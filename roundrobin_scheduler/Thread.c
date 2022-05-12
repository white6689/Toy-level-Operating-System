#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "table.h"

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sched.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <signal.h>

int thread_create(thread_t *thread, thread_attr_t *attr, int priority, void *(*start_routine) (void *), void *arg)
{   
    // 생성
    int pid=clone(start_routine, 1024*64,SIGCHLD|CLONE_FS, arg);
    
    // 죽이기
    kill(pid, SIGSTOP);

    // child tcb 할당
    Thread* tcb=(Thread*)malloc(sizeof(Thread));
    
    // child thread정보를 이용해 tcb 초기화
    tcb->pid=pid;
    tcb->priority=priority;
    tcb->stackSize=1024*64;
    //pid를 할당하기 위해 ThreadTblEnt를 처음부터 돌면서 빈 곳을 찾아 할당한다. 만약 빈곳이 없다면?
    for(int i=0;i<MAX_THREAD_NUM;i++){
        if(pThreadTbEnt[i].bUsed==0||pThreadTbEnt[i].pThread==NULL){
            *thread=i;
            pThreadTbEnt[i].pThread=tcb;
            pThreadTbEnt[i].bUsed=1;
            break;
        }
    }
    tcb->stackAddr=(void*)tcb;
    
    // 현재 실행중인 thread, child thread의 priority 비교
    int now_tid=thread_self();
    Thread* now_thread=pThreadTbEnt[now_tid].pThread;

    if(now_thread->priority<priority){  // child thread priority 낮다 -> status=READY/readyqueue 이동
        tcb->status=THREAD_STATUS_READY;
        InsertThreadToTail(tcb);
    }
    else // 높다 -> context switching
    {
        InsertThreadToTailReadyQueue(now_thread);
        now_thread->status=THREAD_STATUS_READY;
        tcb->status=THREAD_STATUS_RUN;
        // context switching ? parameter 확인하기
        __ContextSwitch(getpid(), pid);
    }
    return 1;
}

int thread_suspend(thread_t tid)
{
    // 해당 thread 실행중지
    Thread* thread=pThreadTbEnt[tid].pThread;
    if(thread==NULL)
        return -1;
    InsertThreadIntodWaitingqueue(thread);
    thread->status=THREAD_STATUS_WAIT;
    return 0;
}

int thread_cancel(thread_t tid)
{
    // 해당 thread 취소
    Thread* target_thread=pThreadTbEnt[tid].pThread;
    KILL(target_thread->pid, SIGKILL);
    DeleteThreadFromWaitingqueue(target_thread);
    DeleteThreadReadyQueue(target_thread);
    if(target_thread!=NULL){
        pThreadTbEnt[tid].pThread=NULL;
        pThreadTbEnt[tid].bUsed=-1;
        free(target_thread);
    }
}

int thread_resume(thread_t tid)
{
    // 해당 thread 재시작
    Thread* target_thread=pThreadTbEnt[tid].pThread;
    Thread* current_thread=pThreadTbEnt[thread_self()].pThread;
    // target이 우선순위가 높다면, 즉 값이 작다면
    if(target_thread->priority<current_thread->priority){
        InsertThreadToTailReadyQueue(current_thread);
        current_thread->status=THREAD_STATUS_READY;
        DeleteThreadFromWaitingqueue(target_thread);
        target_thread->status=THREAD_STATUS_RUN;
        __ContextSwitch(current_thread, target_thread);
    }
    else
    {
        target_thread->status=THREAD_STATUS_READY;
        DeleteThreadFromWaitingqueue(target_thread);
        InsertThreadToTailReadyQueue(target_thread);
    }
    return;
}
int	thread_join(thread_t tid, void** retval){
    // 해당 thread가 종료될 때까지 기다림
}
int thread_exit(void* retval){

}
thread_t thread_self()
{
    // ThreadTbEnt의 index를 반환
    int pid=getpid(); // 자식 thread에서 돌아가기 때문에 getpid는 자식 thread의 pid를 반환할 것이다.
    for(int i=0;i<MAX_THREAD_NUM;i++){
        if(pid==pThreadTbEnt[i].pThread->pid){
            return i;
        }
    }
    return -1;
}
