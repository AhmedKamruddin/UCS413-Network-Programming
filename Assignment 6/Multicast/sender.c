#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>

int main()
{
    char sendline[100];
    int sockfd;
    struct sockaddr_in group;
    struct in_addr local_int;  //local_int interface

    sockfd=socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&group, sizeof(group));
    group.sin_family=AF_INET;
    group.sin_port=htons(22000);
    group.sin_addr.s_addr=inet_addr("226.1.2.3");

    local_int.s_addr=INADDR_ANY;

    setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char*)&local_int, sizeof(local_int));

    for(;;)
    {
        bzero(sendline, sizeof(sendline));
        fgets(sendline, 100, stdin);
        sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr*)&group, sizeof(group));
    }
}