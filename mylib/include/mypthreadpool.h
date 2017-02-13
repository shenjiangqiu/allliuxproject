 ///
 /// @file    mypthreadpool.h
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-13 09:49:46
 ///
#pragma once 
#include <head.h>
typedef void *(*func)(void*);

/* node of queue	*/
typedef struct MyNode
{
	int				_newfd;
	struct MyNode*	_pNext;
}Node,*pNode;

/* queue of newfd	*/
typedef struct tag_work_que
{
	pNode	_phead,_ptail;
	int		_size;
	tag_work_que();				
	~tag_work_que();
	void push(int newfd,struct tag_factory* pfac);
	int	 top(pNode *ppnod);
}Work_Que,*pWork_Que;


/*	struct tag_factory:infomation of thread	*/
typedef struct tag_factory		
{
	pthread_t *		_pth;		//arr of pthread_ts
	int				_tnum;		//num of thread;
	func			_myfunc;	//entance of ptread
	pthread_cond_t	_cond;
	pthread_mutex_t _mutex;
	int				_capality;	//max sizeof que
	Work_Que		_que;		//the newfd que
	bool			_start;		//is stabilished 
	
	~tag_factory();
	tag_factory(int count,int capality);
	int init();
}factory,*pfactory;

/*	the entrance of thread */
void*	pthstart(void *);

int		CreatPthread(int count,pthread_t *pth,pfactory p);
