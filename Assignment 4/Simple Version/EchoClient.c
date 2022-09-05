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
    
	sockfd=socket(AF_INET, SOCK_DGRAM, 0);
    
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(22000);

	
    while(1)
    {
        bzero(sendline, 100);
        fgets(sendline, 100, stdin);         
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *) &servaddr, sizeof(servaddr));
        
        bzero(recvline, 100);
        recvfrom(sockfd, recvline, 100, 0, NULL, NULL);  
        printf("%s", recvline);
    }
}