#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

int main()
{
    char recvline[100];
    char sendline[100];
    int sockfd;
    struct sockaddr_in saddr, caddr;
    socklen_t caddrsize=sizeof(caddr);
    
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&saddr, sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(22000);
    saddr.sin_addr.s_addr=htonl(INADDR_ANY);

    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));

    for(;;)
    {
        bzero(recvline, 100);
        recvfrom(sockfd, recvline, 100, 0, (struct sockaddr*)&caddr, &caddrsize);
        printf("Received %s", recvline);

        bzero(sendline, 100);
        fgets(sendline, 100, stdin);
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr*)&caddr, caddrsize);
    }   

}