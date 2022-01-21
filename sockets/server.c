#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#include<errno.h>

int main()
{
	int sfd,cfd,status,addr_len;
	ssize_t bytes_received;
	char data[100];

	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("error creating socket:\n");
		return -1;
	}
	struct sockaddr_in server_addr,client_addr;

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(1234);
	server_addr.sin_addr.s_addr=inet_addr("192.168.1.18");
	
        
	status = bind(sfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in));
	if(status == -1)
	{
		perror("error while binding address\n");
		return -1;
	}
	status=listen(sfd,2);

	if(status == -1)
	{
		perror("error while listening to port\n");
		return -1;
	}
	
	addr_len=sizeof(struct sockaddr_in);

	cfd=accept(sfd,(struct sockaddr*)&client_addr,&addr_len);

	char* str="hello client this is server";

	ssize_t bytes_sent;
	bytes_sent = send(cfd,str,strlen(str),0);
	if(bytes_sent == -1)
	{
		perror("error while sending bytes\n");
		return -1;
	}
	bytes_received=recv(cfd,data,100,0);
	
	if(bytes_received == -1)
	{
		perror("error while receiving bytes\n");
		return -1;
	}
	
	printf("%s:\n",data);
	close(cfd);
	close(sfd);
	
	return 0;
}
