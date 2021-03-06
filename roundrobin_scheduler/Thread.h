#ifndef __THREAD_H__
#define __THREAD_H__

#include <sched.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#define TIMESLICE		(2)
#define MAX_READYQUEUE_NUM	(8)	/* Ready queue의 개수 */
#define MAX_THREAD_NUM		(64)	/* 생성 가능한 최대 Thread의 개수 */

typedef int	BOOL;
typedef int	thread_t;
typedef struct _Thread Thread;
typedef void	thread_attr_t;

typedef enum{
	THREAD_STATUS_RUN = 0,
	THREAD_STATUS_READY = 1,
	THREAD_STATUS_WAIT = 2,
	THREAD_STATUS_ZOMBIE = 3,
} ThreadStatus;

typedef struct _Thread{ // TCB
	int		stackSize;
	void*		stackAddr;
	ThreadStatus	status;
	int		exitCode;
	pid_t		pid;
	int		priority;
	Thread*		phNext;
	Thread*		phPrev;
} Thread;

typedef struct _ReadyQueueEnt {
	int	queueCount;
	Thread* pHead;
	Thread* pTail;
} ReadyQueueEnt;

typedef struct _ThreadTblEnt {
	BOOL	bUsed;   
	Thread* pThread;
} ThreadTblEnt;


/* head and tail pointers for ready queue */
ReadyQueueEnt pReadyQueueEnt[MAX_READYQUEUE_NUM];

/* head and tail pointers for waiting queue */
Thread* pWaitingQueueHead;
Thread* pWaitingQueueTail;
ThreadTblEnt pThreadTbEnt[MAX_THREAD_NUM];

int 		thread_create(thread_t *thread, thread_attr_t *attr, int priority, void *(*start_routine) (void *), void *arg);
int 		thread_suspend(thread_t tid);
int 		thread_cancel(thread_t tid);
int		thread_resume(thread_t tid);
int			thread_join(thread_t tid, void** retval);
int 		thread_exit(void* retval);
thread_t 		thread_self();


#endif /* __THREAD_H__ */

