#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main()
{
    char sendline[100];
    int sockfd;
    int broadcast=1;
    struct sockaddr_in saddr;
    
    sockfd=socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&saddr, sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(22000);
    saddr.sin_addr.s_addr=inet_addr("172.16.95.255");
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast));

    bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));

    for(;;)
    {
        bzero(sendline, 100);
        fgets(sendline, 100, stdin);
        sendto(sockfd, sendline, 100, 0, (struct sockaddr*)&saddr, sizeof(saddr));
    }
}