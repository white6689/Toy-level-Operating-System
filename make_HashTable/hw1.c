#include "hw1.h"

//malloc.h 사용 불가

void Init(){
    
    //FreeList의 head, tail에 메모리를 할당한다. 할당 불가능(malloc.h 없음)
    pFreeListTail=NULL;
    pFreeListHead=NULL;
}

void InsertObjectToTail(Object* pObj, int ObjNum){
    //pObj의 objnum을 ObjNum으로 설정한 뒤 HashTable의 Tail에 삽입한다. 
    //pHashTableEnt[i]의 형태: double linked list
    //i=hash_function(object_number%arry_length)
    
    int index=ObjNum%HASH_TBL_SIZE;
    pObj->objnum=ObjNum;
    //만약 HashTable에 elmt가 없다면 pObj가 pHead, pTail
    if(pHashTableEnt[index].elmtCount==0){
        pHashTableEnt[index].pHead=pObj;
        pHashTableEnt[index].pTail=pObj;
    }
    else{
        Object* temp=pHashTableEnt[index].pTail;
        pHashTableEnt[index].pTail=pObj;
        temp->phNext=pHashTableEnt[index].pTail;
        pHashTableEnt[index].pTail->phPrev=temp;
    }
    pHashTableEnt[index].elmtCount+=1;
    //printf("pHashTableEnt[%d]'s Head: %p\n", index, pHashTableEnt[index].pHead);
}

void InsertObjectToHead(Object* pObj, int objNum){
    //pObj의 objnum을 objNum으로 설정한 뒤 HashTable의 Head에 삽입한다. 
    //pHashTableEnt[i]의 형태: double linked list
    //i=hash_function(object_number%arry_length)
    
    int index=objNum%HASH_TBL_SIZE;
    pObj->objnum=objNum;
    //만약 HashTable에 elmt가 없다면 pObj가 pHead, pTail
    if(pHashTableEnt[index].elmtCount==0){
        pHashTableEnt[index].pHead=pObj;
        pHashTableEnt[index].pTail=pObj;
    }
    else{
        Object* temp=pHashTableEnt[index].pHead;
        pHashTableEnt[index].pHead=pObj;
        temp->phPrev=pHashTableEnt[index].pHead;
        pHashTableEnt[index].pHead->phNext=temp;
    }
    pHashTableEnt[index].elmtCount+=1;
    //printf("pHashTableEnt[%d]'s Head: %p\n", index, pHashTableEnt[index].pHead);
}

Object* GetObjectByNum(int objnum){    
    //objnum을 이용해 HashTable에 있는 object의 포인터를 반환한다.
    //실패시 NULL반환
    //printf("GetObjectByNum: objnum(%d)\n", objnum);
    int index=objnum%HASH_TBL_SIZE;
    Object* temp=pHashTableEnt[index].pHead;
    for(int j=0;j<pHashTableEnt[index].elmtCount;j++){
        if(temp->objnum==objnum)
            return temp;
        temp=temp->phNext;
    }
    return NULL;
}

Object* GetObjectFromObjFreeList(){
    //freelist의 tail을 반환 및 삭제
    //실패시 NULL 반환, freeList에 아무 object가 없을 때 발생(Head가 Tail을 가리키고 있을 때)
    
    Object* temp=pFreeListTail;
    if(temp==NULL){
        //printf("GetObject NULL\n");
        return NULL;
    }

    if(pFreeListHead==pFreeListTail){
        //printf("GetObject same.. ");
        pFreeListHead=NULL;
        pFreeListTail=NULL;
    }
    else
    {
        Object* temp2=pFreeListTail->phPrev;
        pFreeListTail=temp2;
    }
    //printf("GetObject %p, pTail: %p\n", temp, pFreeListTail);

    return temp;
}

BOOL DeleteObject(Object* pObj){
    //HashTable에서 해당 pObj를 삭제한다.
    //성공시 TRUE 반환
    //실패시 FALSE 반환, HashTable에 해당 pObj가 없을 때 발생
    
    // printf("DeleteObject: %p/%d\n", pObj, pObj->objnum);
    int index=pObj->objnum%HASH_TBL_SIZE;
    if((pHashTableEnt[index].pHead==pObj)&&(pHashTableEnt[index].pTail==pObj)){
        // printf("This is last one: %p/%d\n", pObj, pObj->objnum);
        pHashTableEnt[index].pHead=NULL;
        pHashTableEnt[index].pTail=NULL;
    }
    else if(pHashTableEnt[index].pHead==pObj){
        pHashTableEnt[index].pHead=pHashTableEnt[index].pHead->phNext;
        pHashTableEnt[index].pHead->phPrev=NULL;
    }
    else if(pHashTableEnt[index].pTail==pObj){
        pHashTableEnt[index].pTail=pHashTableEnt[index].pTail->phPrev;
        pHashTableEnt[index].pTail->phNext=NULL;
    }
    else
    {
        //해당 pObj가 HashTable에 없을 경우? 해당 index에 pObj가 없을 경우
        //chk가 1일 경우 있음, 0일 경우 없음 return false
        int chk=0;
        Object* temp=pHashTableEnt[index].pHead;
        for(int j=0;j<pHashTableEnt[index].elmtCount;j++){
            if(temp==pObj)
                chk=1;
            temp=temp->phNext;
        }
        if(chk==0)
            return 0;
        pObj->phNext->phPrev=pObj->phPrev;
        pObj->phPrev->phNext=pObj->phNext;
    }
    pObj->phNext=NULL;
    pObj->phPrev=NULL;
    pHashTableEnt[index].elmtCount-=1;
    return 1;
}

void InsertObjectIntoObjFreeList(Object* pObj){
    //obect가 더이상 쓰이지 않는다면 freelist의 head에 삽입한다.
    //freelist에 아무 object가 없는 상태라면, object의 갯수는 OBJ_INVALID로 설정한다.
    //freelist의 형태: double linked list
    
    //HEAD에 object를 넣는 순서
    //1. HEAD의 phNext를 object로 연결
    //2. object의 phPrev를 HEAD로 연결
    //3. object의 phNext는 원래 HEAD의 phNext가 가리키고 있던 object

    // printf("Do insert Object into FreeList %d\n", pObj->objnum);
    if(pFreeListHead==NULL){
        pFreeListHead=pObj;
        pFreeListTail=pObj;
    }
    else if(pFreeListHead==pFreeListTail){
        pFreeListHead=pObj;
        pFreeListHead->phNext=pFreeListTail;
        pFreeListTail->phPrev=pFreeListHead;
    }
    else{
        Object* temp=pFreeListHead;
        pFreeListHead=pObj;
        pFreeListHead->phNext=temp;
        temp->phPrev=pFreeListHead;
    }
    //printf("Insert Obj into FreeList: %p, PFreeListHead: %p\n", pObj, pFreeListHead);
}

