#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
	char sendline[100];
	char recvline[100];
	int listen_fd, sockfd, i;
	struct sockaddr_in servaddr;
	
	listen_fd=socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(22000);

	bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	listen(listen_fd, 10);
	sockfd=accept(listen_fd, (struct sockaddr*) NULL, NULL);
		
	while(1)
	{
		bzero(recvline, 100);
        bzero(sendline, 100);
		recv(sockfd, recvline, 100, 0);
		printf("%s", recvline);

		int k=0;
		int n=strlen(recvline);
		for(i=n-2; i>=0; i--)
		{
			sendline[k++]=recvline[i];
		}
		sendline[k]='\n';
		
		send(sockfd, sendline, strlen(sendline), 0);
		
	}

}
