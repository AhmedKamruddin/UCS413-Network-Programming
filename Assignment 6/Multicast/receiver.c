#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<netinet/in.h>

int main()
{
    char recvline[100];
    int sockfd;
    int reuse=1;
    struct sockaddr_in local;
    struct ip_mreq group;

    sockfd=socket(AF_INET, SOCK_DGRAM, 0);

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(reuse));

    bzero((struct sockaddr*)&local, sizeof(local));
    local.sin_family=AF_INET;
    local.sin_port=htons(22000);
    local.sin_addr.s_addr=INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&local, sizeof(local));

    group.imr_multiaddr.s_addr=inet_addr("226.1.2.3");
    group.imr_interface.s_addr=INADDR_ANY;

    setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&group, sizeof(group));
    
    for(;;)
    {
        bzero(recvline, sizeof(recvline));
        read(sockfd, recvline, 100);
        printf("Received: %s", recvline);
    }
}