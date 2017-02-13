 ///
 /// @file    mypthreadpool.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-13 09:49:38
 ///

//线程池实现
//
#include"../include/mypthreadpool.h"
#include"../include/sendfile.h"
void *pthstart(void* p)
{	
	pfactory myfac=(pfactory)p;
	int newfd;
	pNode tempnode;
	while(1)
	{
		pthread_mutex_lock(&myfac->_mutex);
		while(myfac->_que._size==0)
		{
			pthread_cond_wait(&myfac->_cond,&myfac->_mutex);
		}
		myfac->_que.top(&tempnode);
		pthread_mutex_unlock(&myfac->_mutex);
		newfd=tempnode->_newfd;
		delete tempnode;
		sendfile("file",newfd);
		
	}
	return NULL;
}

int CreatPthread(int count,pthread_t *pth,pfactory p)
{
	int i;
	for(i=0;i<count;++i)
	{
		pthread_create(&pth[i],NULL,pthstart,p);
	}
	return 0;
}
tag_work_que::tag_work_que()
	:_phead(NULL)
	,_ptail(NULL)
	,_size(0){}

	
/*void tag_work_que::pop()
{
	if(_size==0)
	{
		return;
	}
	if(_size==1)
	{
		delete _phead;
		_phead=NULL;
		_ptail=NULL;
		--_size;
		return;
	}
	pNode temp=_phead;
	_phead=_phead->_pNext;
	--_size;
	delete temp;
	return;

}*/

int  tag_work_que::top(pNode *ppnod)
{
	
	*ppnod=_phead;
	if(_size==1)
	{
		_phead=NULL;
		_ptail=NULL;
		--_size;
	}
	else
	{
		--_size;
		_phead=_phead->_pNext;
	}
	return 0;
}
void tag_work_que::push(int newfd,pfactory pfac)
{
	pNode ptemp=new Node;
	ptemp->_newfd=newfd;
	ptemp->_pNext=NULL;
	pthread_mutex_lock(&pfac->_mutex);
	if(_size==0)		
	{
		_phead=_ptail=ptemp;
		++_size;
		
	}
	else
	{
		_ptail->_pNext=ptemp;
		_ptail=ptemp;
		++_size;
	}
	pthread_mutex_unlock(&pfac->_mutex);
	
}

tag_factory::tag_factory(int count,int capality)
	:_pth(new pthread_t[count])
	,_tnum(count)
	,_capality(capality)
	,_que()
	,_start(false)
{
	_myfunc=pthstart;
	pthread_cond_init(&_cond,NULL);
	pthread_mutex_init(&_mutex,NULL);
}
tag_factory::~tag_factory()
{
	delete[] _pth;
}
Work_Que::~tag_work_que()
{
	pNode temp;
	while(_size--)
	{
		temp=_phead;
		_phead=_phead->_pNext;
		delete temp;
	}
}

int tag_factory::init()
{
	int ret=CreatPthread(_tnum,_pth,this);
	if(ret==-1)
	{
		cout<<"error CreatPthread"<<endl;
		return -1;
	}
	_start=true;
	return 0;
}
