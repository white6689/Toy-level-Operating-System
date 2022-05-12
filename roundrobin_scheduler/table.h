#ifndef __TABLE_H__
#define __TABLE_H__

void InsertThreadToTailReadyQueue(Thread* pObj);
Thread* DeleteThread(int priority){
void DeleteThreadFromWaitingqueue(Thread* pObj);
void InsertThreadIntodWaitingqueue(Thread* pObj);

#endif