#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<linux/in.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

void get_ipaddress(const char* node,const char* port)
{
	int sfd,cfd,status,addr_len;
	
	struct addrinfo hints, *server_info, *p;
	struct sockaddr_storage client_addr;
	socklen_t sin_size;
	char ip_addr[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints,0,sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_sock_type = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// 
	
	if((rv = getaddrinfo(node,PORT,&hints,&servinfo))!=0)   
	{
		perror("getaddrinfo:");
		return -1;
	}
}

int main()
{
	int cfd,status;
	struct sockaddr_in caddr;

	ssize_t bytes_sent,bytes_received;

	char received[100];

	cfd=socket(AF_INET,SOCK_STREAM,0);

	caddr.sin_family = AF_INET;
	caddr.sin_addr.s_addr = inet_addr("192.168.1.18");
	caddr.sin_port = htons(1234);
	
	status = connect(cfd,(struct sockaddr*)&caddr,sizeof(struct sockaddr_in));
	if(status == -1)
	{
		perror("error while connecting\n");
		return -1;
	}

	char* str="Hello server this is client";

	bytes_sent = send(cfd,str,strlen(str),0);

	if(bytes_sent == -1)
	{
		perror("error while connecting\n");
		return -1;
	}
		
	bytes_received = recv(cfd,received,100,0);

	if(bytes_received == -1)
	{
		perror("error while receiving data\n");
		return -1;
	}
	
	printf("%s\n",received);

	while(1);
	close(cfd);

	return 0;	

}
