#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE *fp=popen("ls -la","r");
	char buff[512]={0};
	while(fgets(buff,sizeof(buff),fp))
	{
		puts(buff);

	}
	pclose(fp);
	return 0;

}
