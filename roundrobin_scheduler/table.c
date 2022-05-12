#include "Init.h"
#include "Thread.h"
#include "table.h"

void InsertThreadToTailReadyQueue(Thread* pObj){
    //pObj의 objnum을 objNum으로 설정한 뒤 HashTable의 Tail에 삽입한다.(과제 사진 참고) 
    //pReadyQueueEnt[i]의 형태: double linked list
    //i=Thread.priority

    int index=pObj->priority;

    //만약 HashTable에 elmt가 없다면 pObj가 pHead, pTail
    if(pReadyQueueEnt[index].queueCount==0){
        pReadyQueueEnt[index].pHead=pObj;
        pReadyQueueEnt[index].pTail=pObj;
    }
    else{
        Thread* temp=pReadyQueueEnt[index].pTail;
        pReadyQueueEnt[index].pTail=pObj;
        temp->phPrev=pReadyQueueEnt[index].pTail;
        pReadyQueueEnt[index].pHead->phNext=temp;
    }
    pReadyQueueEnt[index].queueCount+=1;
    //printf("pHashTableEnt[%d]'s Head: %p\n", index, pHashTableEnt[index].pHead);
}


void DeleteThreadFromWaitingqueue(Thread* pObj){
    // waiting queue에 있는 thread를 삭제
    if(pObj==pWaitingQueueHead){
        pWaitingQueueHead=pObj->phNext;
        pWaitingQueueHead->phPrev=NULL;
        pObj->phNext=NULL;
    }
    else if(pObj==pWaitingQueueTail){
        pWaitingQueueTail=pObj->phPrev;
        pWaitingQueueTail->phNext=NULL;
        pObj->phPrev=NULL;
    }
    else{
        Thread* temp=pObj->phPrev;
        temp->phNext=pObj->phNext;
        pObj->phNext->phPrev=temp;
        pObj->phNext=NULL;
        pObj->phPrev=NULL;
    }
}

Thread* DeleteThread(int priority){
    //HashTable에서 해당 우선순위 queue의 Head pObj(thread)를 삭제한다.
    //성공시 TRUE 반환
    //실패시 FALSE 반환, 해당 우선순위 HashTable에 아무것도 없을 경우 발생한다.
    if(pReadyQueueEnt[priority].queueCount==0)
        return NULL;

    Thread* temp=pReadyQueueEnt[priority].pHead;
    if((pReadyQueueEnt[priority].queueCount==1)){
        pReadyQueueEnt[priority].pHead=NULL;
        pReadyQueueEnt[priority].pTail=NULL;
    }
    else if(pReadyQueueEnt[priority].queueCount==2){
        pReadyQueueEnt[priority].pTail=pReadyQueueEnt[priority].pHead->phPrev;
        pReadyQueueEnt[priority].pTail->phNext=NULL;
    }
    else
    {
        pReadyQueueEnt[priority].pHead=temp->phPrev;
        pReadyQueueEnt[priority].pHead->phNext=NULL;
    }
    temp->phNext=NULL;
    temp->phPrev=NULL;
    pReadyQueueEnt[priority].queueCount-=1;
    return temp;
}

void InsertThreadIntodWaitingqueue(Thread* pObj){
    //thread가 더이상 쓰이지 않는다면 waiting queue의 tail에 삽입한다.
    //waiting queue 아무 object가 없는 상태라면, thread의 갯수는 OBJ_INVALID로 설정한다.
    // waiting queue 형태: double linked list
    
    //HEAD에 thread 넣는 순서
    //1. HEAD의 phNext를 object로 연결
    //2. object의 phPrev를 HEAD로 연결
    //3. object의 phNext는 원래 HEAD의 phNext가 가리키고 있던 object

    // printf("Do insert Object into FreeList %d\n", pObj->objnum);
    if(pWaitingQueueHead==NULL){
        pWaitingQueueHead=pObj;
        pWaitingQueueTail=pObj;
    }
    else if(pWaitingQueueHead==pWaitingQueueTail){
        pWaitingQueueTail=pObj;
        pWaitingQueueHead->phNext=pWaitingQueueTail;
        pWaitingQueueTail->phPrev=pWaitingQueueHead;
    }
    else{
        Thread* temp=pWaitingQueueTail;
        pWaitingQueueTail=pObj;
        pWaitingQueueTail->phPrev=temp;
        temp->phNext=pWaitingQueueTail;
    }
    //printf("Insert Obj into FreeList: %p, PFreeListHead: %p\n", pObj, pFreeListHead);
}


