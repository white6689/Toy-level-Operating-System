#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "table.h"

int RunScheduler( void )
{
    //while?

    for(int i=0;i<MAX_READYQUEUE_NUM;i++){
        if(pReadyQueueEnt[i].queueCount>0){
            InsertThreadToTailReadyQueue(pCurrentThread);
            Thread* selected_thread=DeleteThread(i);
            __ContextSwitch(pCurrentThread->pid, selected_thread->pid);
            break;
        }
    }
    alarm(TIMESLICE);
}


void __ContextSwitch(int curpid, int newpid)
{
    KILL(curpid, SIGSTOP);
    KILL(newpid, SIGCONT);
}
