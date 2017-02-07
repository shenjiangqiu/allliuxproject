//
/// @file    head.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-06 21:20:56
///
#define ischat(a) (a[1][0]=='c'?1:0)
#define isu1(a) (a[2][1]=='1'?1:0)
#include"head.h"
void sig(int signum)
{
	return;
}
int ShowWindow(char **argv)
{
	signal(SIGALRM,sig);
	if(ischat(argv))//chat window
	{
		//开始和显示窗口同步
		int shmid;
		int key;
		if(isu1(argv))
			key=1101;//shmid=shmget(1101,4096,IPC_CREAT|0600);
		else
			key=1102;//shmid=shmget(1102,4096,IPC_CREAT|0600);
		shmid=shmget(key,4096,IPC_CREAT|0600);
		if(shmid==-1)
		{
			perror("shmget");
			exit(-1);
		}
		char *buf=(char*)shmat(shmid,NULL,0);
		if(buf==(char*)-1)
		{
			perror("shmat");
			exit(-1);
		}
		memset(buf,0,4096);
		pid_t myid=getpid();
		sprintf(buf,"%s %d","-d",myid);
		cout<<"start to wait for signal"<<endl;
		pause();
		cout<<"down!"<<endl;
		char cmd[10];
		pid_t rmid;
		sscanf(buf,"%s%d",cmd,&rmid);
		kill(rmid,SIGALRM);
		//同步完毕

		//开始和另一个chat同步
		mkfifo("chatfifo",0666);
		char fifonamesend[10];
		char fifonameget[10];
		if(isu1(argv))
		{
			strcpy(fifonamesend,"u1tou2");
			strcpy(fifonameget,"u2tou1");
		}
		else
		{
			strcpy(fifonamesend,"u2tou1");
			strcpy(fifonameget,"u1tou2");
		}
		int ret=mkfifo(fifonamesend,0666);
		if(ret<0)
			return -2;
		int fd[2];
		if(isu1(argv))
			fd[0]=open(fifonamesend,O_WRONLY);
		while(1)
		{
			fd_set fdin;
			FD_ZERO(&fdin);
			FD_SET(fd[1],&fdin);
			FD_SET(STDIN_FILENO,&fdin);
			select(fd[1]+1,&fdin,NULL,NULL,NULL);

		}	

		//unlink("chatfifo",0666);
	}
	else//show window
	{
		int shmid;
		char *buff;
		if(isu1(argv))
		{
			cout<<"start to wait chat!"<<endl;
			while(1)
			{
				shmid=shmget(1101,4096,0600);
				if(shmid>0)
				{
					buff=(char*)shmat(shmid,NULL,0);
					if(buff[0]=='-')
						break;
					shmdt(buff);
				}
				sleep(1);
			}
			cout<<"connet shm!"<<endl;
			char *buff=(char*)shmat(shmid,NULL,0);
			if(buff==(char*)-1)
			{
				exit(-1);
			}
			char cmd[10];
			int pidofchat;
			sscanf(buff,"%s%d",cmd,&pidofchat);
			kill(pidofchat,SIGALRM);
			cout<<"send kill !"<<endl;
			return 0;

		}

	}
}
