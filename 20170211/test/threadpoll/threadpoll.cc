 ///
 /// @file    threadpoll.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-11 10:07:58
 ///
 
#include <head.h>
#ifndef __WORK_QUE__
#define __WORK_QUE__




typedef struct tag_node
{
	int nd_sockfd;
	struct tag_node *nd_next;
}node_t,*pnode_t;

typedef struct tag_que
{
	pnode_t que_head,que_tail;
	int que_capacity;
	int que_size;
	pthread_mutex_t que_mutex;

}que_t,*pque_t;

void factory_que_init(pque_t pq,int capacity);
void factory_que_set(pque_t pq,pnode_t pnew);
void factory_que_get(pque_t pq,pnode_t* p);
void factory_que_destroy(pque_t pq);
int factory_que_full(pque_t pq);
int factory_que_empty(pque_t pq);
#endif
int main()
{}
