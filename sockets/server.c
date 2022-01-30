/*
 * This code is taken from https://beej.us/guide/bgnet/
 */





#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netdb.h>
#include<signal.h>
#include<sys/wait.h>

#define PORT "3490"

#define BACKLOG 10

void sigchld_handler(int s)
{
	int saved_errno = errno;

	while(waitpid(-1,NUULL,WNOHANG) > 0);
	
	errno = saved_errno;
};

void *get_in_addr(struct sockaddr* sa)
{
	if(sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in*)sa)->sin6_addr);
}

int main(int argc,char* argv[])
{
	int sfd,cfd,status,addr_len;
	
	struct addrinfo hints, *server_info, *p;
	struct sockaddr_storage client_addr;
	socklen_t sin_size;
	struct sigaction sa;
	int yes = 1;
	char ip_addr[INET6_ADDRSTRLEN];
	int rv;

	memset(&hints,0,sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_sock_type = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	// 
	
	if((rv = getaddrinfo(NULL,PORT,&hints,&servinfo))!=0)   
	{
		perror("getaddrinfo:");
		return -1;
	}

	for(p=servinfo; p != NULL;p = p->ai_next)
	{
		if((sfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol)) == -1)
		{
			perror("server: socket");
			continue;
		}
		if(setsockopt(sfd,SOL_SOCK,SO_REUSEADDR,&yes,sizeof(int)) == -1)
		{
			perror("setsocketopt:");
			return -1;
		}
		if(bind(sfd,p->ai_addr,p->ai_addrlen) == -1)
		{
			perror("server: bind");
			continue;
		}

	}

	freeaddr(servinfo);

	if(p == NULL)
	{
		fprintf(stderr,"server failed to bind\n");
		exit(1);
	}

	if(listen(sfd,BACKLOG) == -1)
	{
		perror("listen");
		exit(1);
	}


	if(status == -1)
	{
		perror("error while listening to port\n");
		return -1;
	}

	sa.sa_handler = sigchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if(sigaction(SIGCHILD,&sa,NULL) == -1)
	{
		perror("signaction");
		exit(1);
	}
	
	printf("server: waiting for connections....\n");
	char* str="hello client this is server";

	while(1)
	{
		sin_size = sizeof(client_addr);
		cfd = accept(sfd,(struct sockaddr*)&client_addr,&sin_size);

		if(new_fd == -1)
		{
			perror("accept");
			continue;
		}

		inet_ntop(client_addr.ss_family,get_in_addr((struct sockaddr*)&client_addr),ip_addr,sizeof(ip_addr));
		printf("server got connected to %s\n",ip_addr);

		if(!fork()) //child process
		{
			close(sfd);
			if(send(cfd,str,strlen(str),0) == -1))
			{
				perror("send:");
			}
			close(cfd);
			exit(0);
		}
		close(cfd);//parent doesnt need this



	}
	
	
	return 0;
}
