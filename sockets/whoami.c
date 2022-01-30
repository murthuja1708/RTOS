#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>

int main(int argc,char* argv[])
{
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd == -1)
	{
		exit(EXIT_FAILURE);
	}


	char host[50]={'\0'};
	
	if( gethostname(host,50) == -1)
	{
		exit(EXIT_FAILURE);
	}
	printf("%s\n",host);

	return 0;
}
