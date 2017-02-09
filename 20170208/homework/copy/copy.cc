 ///
 /// @file    copy.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-08 23:33:14
 ///
 
#include<head.h>
char *mmaddr;
int fdwt[10];
void *thd(void *p)
{
	cout<<"th start!"<<endl;
	long sec=(long)p;
	char* myaddr=mmaddr+sec*100000000;
	for(int i=0;i<1000000;++i)
	{
		int ret=write(fdwt[sec],myaddr+i*100,100);
		if(ret<100)
		
		{
			cout<<"error"<<endl;
			perror("write");
			exit(0);

		}

	}
	close(fdwt[sec]);
	return NULL;
}
int main()
{
	int fdrd;
	fdrd=open("a.txt",O_RDONLY|O_CREAT,0666);
	if(fdrd==-1)
	{
		perror("open");
		return -1;
	}
	int ret;
	mmaddr=(char*)mmap(NULL,1000000000,PROT_READ,MAP_SHARED,fdrd,0);
	if(mmaddr==(char*)-1)
	{
		perror("mmap");
		return -1;
	}
	for(int i=0;i<10;++i)
	{
		ret=fdwt[i]=open("b.txt",O_WRONLY|O_CREAT,0666);
		if(ret==-1)
		{
			perror("open");
			return -1;
		}
		ret=lseek(fdwt[i],i*100000000,SEEK_SET);
		if(ret!=i*100000000)
		{
			perror("lseek");
			return -1;
		}
	}
	pthread_t pthid[10];
	for(int i=0;i<10;i++)
	{
		pthread_create(&pthid[i],NULL,thd,(void *)(long int)i);

	}
	for(int i=0;i<10;++i)
	{
		pthread_join(pthid[i],NULL);
	}
	munmap((void *)mmap,1000000000);
	close(fdrd);


	return 0;
}
