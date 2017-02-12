#pragma once

#include<head.h>
typedef struct proc_child
{
	int pid;
	int fdw;
	bool isbusy;
}ch,*pch;
int make_child(pch,int);
int handle(int);

