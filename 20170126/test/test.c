#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
		return -1;

	FILE *fp;

	fp=popen(argv[1],"r");
	if(NULL==fp)
		return -1;
	char buff[100];
	int ret;
	while(ret=fgets(buff,sizeof(buff),fp))
	{
		fputs(buff,stdout);
	}
	pclose(fp);
	return 0;


}
