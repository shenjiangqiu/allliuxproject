//
/// @file    head.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-06 21:20:56
///
#define ischat(a) (a[1][0]=='c'?1:0)
#define isu1(a) (a[2][1]=='1'?1:0)
#include"head.h"
typedef struct tag_info
{
	char **argv;
	pid_t rmpid,spid;
	char* shmaddr;
	int shmid;
	int fd[2];
}info;
info *pinfo;
void sig(int signum)
{ 
	int ret;
	if(signum==SIGALRM)
		return;
	if(signum==SIGINT||signum==SIGQUIT)
	{

		if(ischat(pinfo->argv))
		{

			cout<<"start clean fd"<<endl;
			kill(pinfo->spid,SIGUSR1);
			kill(pinfo->rmpid,SIGUSR1);
			sleep(1);
			ret=close(pinfo->fd[0]);
			if(!ret)
			{
				perror("close fd[0]");
				exit(0);
			}
			ret=close(pinfo->fd[1]);
			if(!ret)
			{
				perror("close fd[1]");
				exit(0);
			}
			cout<<"fd succ"<<endl;
			//if(pinfo->rmpid!=0)
			ret=shmdt(pinfo->shmaddr);
			if(!ret)
			{
				perror("shmdt");
				exit(0);
			}
			ret=shmctl(pinfo->shmid,IPC_RMID,NULL);
			if(!ret)
			{
				perror("shmctl rm pinfo->shmid");
				exit(0);
			}
			exit(0);	
		}
		else
		{
			kill(pinfo->rmpid,SIGUSR2);
			cout<<"the shmaddr:"<<shmaddr<<endl;
			ret=shmdt(pinfo->shmaddr);
			if(!ret)
			{
				perror("shmdt");
				exit(0);
			}
			system("clear");
			cout<<"THANKS FOR USING!BYE!"<<endl;
			exit(0);
		}
		return;
	}
	if(signum==SIGUSR1)
	{
		if(ischat(pinfo->argv))
		{
			kill(pinfo->spid,SIGUSR1);
			ret=close(pinfo->fd[0]);
			if(!ret)
			{
				perror("close");
				exit(0);
			}
			ret=close(pinfo->fd[1]);
			if(!ret)
			{
				perror("close");
				exit(0);
			}
			unlink("u1tou2");
			unlink("u2tou1");
			ret=shmdt(pinfo->shmaddr);
			if(!ret)
			{
				perror("shmdt");
				exit(0);
			}
			ret=shmctl(pinfo->shmid,IPC_RMID,NULL);
			if(!ret)
			{
				perror("shmctl");
				exit(0);
			}
			system("clear");
			cout<<"THANKS FOR USING!BYE!"<<endl;
			exit(0);
		}
		else
		{
			cout<<"the shmaddr is"<<endl;
			cout<<pinfo->shmaddr<<endl;
			ret=shmdt(pinfo->shmaddr);
			if(!ret)
			{
				perror("shmdt");
				exit(0);
			}
			system("clear");
			cout<<"THANKS FOR USING!BYE!"<<endl;
			exit(0);
		}
		return;
	}
	if(signum==SIGUSR2)
	{
		kill(pinfo->rmpid,SIGUSR1);
		sleep(1);
		ret=close(pinfo->fd[0]);
		if(!ret)
		{
			perror("close");
			exit(0);
		}
		ret=close(pinfo->fd[1]);
		if(!ret)
		{
			perror("close");
			exit(0);
		}
		shmdt(pinfo->shmaddr);
		if(!ret)
		{
			perror("shmdt");
			exit(0);
		}
		shmctl(pinfo->shmid,IPC_RMID,NULL);
		if(!ret)
		{
			perror("shmctl");
			exit(0);
		}
		system("clear");
		cout<<"THANKS FOR USING!BYE!"<<endl;
		exit(0);

		return;
	}

}
int ShowWindow(char **argv)
{
	
	signal(SIGALRM,sig);
	signal(SIGQUIT,sig);
	signal(SIGINT,sig);
	signal(SIGUSR1,sig);
	signal(SIGUSR2,sig);
	info minfo;
	memset(&minfo,0,sizeof(minfo));	
	pinfo=&minfo;
	pid_t mypid=getpid();
	pinfo->argv=argv;
	pid_t spid;
	char bufftos[100];//显示窗口缓存
	char bufftoc[100];//聊天管道缓存
	char *buf;//共享内存地址
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
		pinfo->shmid=shmid;
		buf=(char*)shmat(shmid,NULL,0);
		if(buf==(char*)-1)
		{
			perror("shmat");
			exit(-1);
		}
		minfo.shmaddr=buf;
		memset(buf,0,4096);
		sprintf(buf,"%s %d","-d",mypid);
		cout<<"start to wait for signal"<<endl;
		pause();
		cout<<"down!"<<endl;
		sscanf(buf,"%s%d",bufftos,&spid);
		//kill(spid,SIGALRM);
		//同步完毕

		//开始和另一个chat同步
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
		int ret;
		if(isu1(argv))
		{
			ret=mkfifo(fifonamesend,0666);
			if(ret==-1)
				return -1;
			ret=mkfifo(fifonameget,0666);
			if(ret==-1)
				return -1;
		}

		int fd[2];
		if(isu1(argv))
		{
			fd[0]=open(fifonamesend,O_WRONLY);
			cout<<"fd[0]="<<fd[0];
			fd[1]=open(fifonameget,O_RDONLY);
			cout<<"fd[1]="<<fd[1];

		}
		else
		{
			while(1)
			{
				if(!access(fifonameget,F_OK))
				{
					fd[1]=open(fifonameget,O_RDONLY);
					cout<<"fd[1]="<<fd[1];

					break;
				}
				sleep(1);
			}
			while(1)
			{
				if(!access(fifonamesend,F_OK))
				{

					fd[0]=open(fifonamesend,O_WRONLY);
					break;
				}
				sleep(1);
			}
		}
		pinfo->fd[0]=fd[0];
		pinfo->fd[1]=fd[1];
		cout<<"管道同步完成开始通信！"<<endl;
		//同步完成！

		system("clear");
		while(1)//开始通讯
		{

			fd_set fdin;
			FD_ZERO(&fdin);
			FD_SET(fd[1],&fdin);
			FD_SET(STDIN_FILENO,&fdin);
			select(fd[1]+1,&fdin,NULL,NULL,NULL);
			if(FD_ISSET(STDIN_FILENO,&fdin))//键盘有输入
			{
				system("clear");
				//cout<<"正在读取数据"<<endl;
				memset(bufftoc,0,sizeof(bufftoc));
				read(STDIN_FILENO,bufftoc,sizeof(bufftoc));
				//	memset(bufftos,0,sizeof(bufftos));
				sprintf(buf,"%s %s","-ms",bufftoc);
				//buf[strlen(buf)-1]=0;
				kill(spid,SIGALRM);
				//cout<<spid<<" "<<buf<<" "<<endl;
				write(fd[0],bufftoc,strlen(bufftoc));
				//cout<<fd[0]<<endl;

			}
			if(FD_ISSET(fd[1],&fdin))
			{
				memset(bufftoc,0,sizeof(bufftoc));
				read(fd[1],bufftoc,sizeof(bufftoc));
				sprintf(buf,"%s %s","-mr",bufftoc);

				kill(spid,SIGALRM);
				//cout<<"sendkill "<<spid<<buf<<endl;
			}
		}	

		//unlink("chatfifo",0666);
	}
	else//show window
	{
		system("clear");		
		cout<<"my id "<<mypid<<endl;
		int shmid;
		int key;
		if(isu1(argv))
		{
			key=1101;
		}
		else key=1102;
		cout<<"start to wait chat!"<<endl;
		while(1)
		{
			shmid=shmget(key,4096,0600);
			if(shmid>0)
			{
				buf=(char*)shmat(shmid,NULL,0);
				if(buf[1]=='d')
					break;
				shmdt(buf);
			}
			sleep(1);
		}
		pinfo->shmid=shmid;
		pinfo->shmaddr=buf;
		cout<<"connet shm!"<<endl;
		char cmd[10];
		int pidofchat;
		sscanf(buf,"%s%d",cmd,&pidofchat);
		//cout<<"pidofcharis "<<pidofchat<<endl;
		pinfo->rmpid=pidofchat;
		memset(buf,0,4096);
		sprintf(buf,"%s %d ","-d",mypid);
		kill(pidofchat,SIGALRM);
		//cout<<"send kill !"<<endl;


		while(1)
		{
			pause();
			//cout<<"收到信号！"<<endl;
			if(buf[2]=='s')
			{
				int temp=strlen(buf+4);
				for(int i=0;i<30-temp;++i)
					printf(" ");
				printf("me: ");
				printf("%s",buf+4);
			}
			else
			{
				printf("he: ");
				printf("%s",buf+4);
			}
		}
		return 0;

	}

}
