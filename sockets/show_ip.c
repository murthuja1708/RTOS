#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>


int main(int argc,char* argv[])
{
	struct addrinfo hints,*res,*p;
	int status;

	char ipstr[100];
	if(argc!=2)
	{
		fprintf(stderr,"usage showip hostname\n");
		return -1;
	}
	memset(&hints,0,sizeof(hints));

	hints.ai_family=AF_INET;
	hints.ai_socktype=SOCK_STREAM;

	if((status=getaddrinfo(argv[1],NULL,&hints,&res))!=0)
	{
		fprintf(stderr,"get addrinfo %s\n",gai_strerror(status));
		return -1;
	}

	printf("ip addresses for %s:\n\n",argv[1]);

	for(p=res;p!=NULL;p=p->ai_next)
	{
		void* addr;
		char* ipver;
		struct sockaddr_in* ipv4=(struct sockaddr_in*)p->ai_addr;
		addr=&(ipv4->sin_addr);
		ipver="IPv4";
		inet_ntop(p->ai_family,addr,ipstr,sizeof(ipstr));
		printf(" %s: %s\n",ipver,ipstr);
	}
	freeaddrinfo(res);
	return 0;
}
