 ///
 /// @file    sendfile.h
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-12 15:50:50
 ///
#pragma once 
#include <head.h>
typedef struct tag_bftype
{
	int len;
	char buff[1024];
}bftype,*pbftype;
int sendfile(const char *filename,int sfd);
int recvfile(int sfd);


