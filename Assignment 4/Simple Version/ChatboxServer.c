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
	int sockfd;
	struct sockaddr_in servaddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;

	sockfd=socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(22000);

	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
	addr_size=sizeof(serverStorage);
		
	while(1)
	{
		/* Try to receive any incoming UDP datagram. Address and port of 
      	requesting client will be stored on serverStorage variable */

		bzero(recvline, 100);
        recvfrom(sockfd, recvline, 100, 0, (struct sockaddr *) &serverStorage, &addr_size);
		printf("%s", recvline);
        
		bzero(sendline, 100);
		fgets(sendline, 100, stdin);
		sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *) &serverStorage, addr_size);
		
	}

}
