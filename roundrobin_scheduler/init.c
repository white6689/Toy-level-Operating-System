#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include <malloc.h>

void Init(void)
{
    //ready queue, waiting queue 만들기(할당?)
    //threadtable bused=0, pThread=NULL로 초기화
    for(int i=0;i<MAX_THREAD_NUM;i++){
        pThreadTbEnt[i].bUsed=0;
        pThreadTbEnt[i].pThread=NULL;
    }

      
    
}