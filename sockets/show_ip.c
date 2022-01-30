#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>

void get_ipaddress(char* node,char* port)
{
	int sfd,cfd,status,addr_len;
	
	struct addrinfo hints, *server_info, *p;
	struct sockaddr_storage client_addr;
	socklen_t sin_size;
	char ipstr[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints,0,sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// 
	
	if((rv = getaddrinfo(node,port,&hints,&server_info))!=0)   
	{
		perror("getaddrinfo:");
		exit(EXIT_FAILURE);
	}
	void* addr;
	for(p=server_info;p!=NULL;p=p->ai_next)
	{
		struct sockaddr_in* ipv4=(struct sockaddr_in*)p->ai_addr;
		addr=&(ipv4->sin_addr);
		inet_ntop(p->ai_family,addr,ipstr,sizeof(ipstr));
		printf("%s\n",ipstr);
	}
	freeaddrinfo(server_info);
}


int main(int argc,char* argv[])
{
	struct addrinfo hints,*res,*p;
	int status;

	if(argc!=2)
	{
		fprintf(stderr,"usage showip hostname\n");
		return -1;
	}

	get_ipaddress(argv[1],"80");


	return 0;
}
