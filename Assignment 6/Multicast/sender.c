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
    char *recipient_ip[2];
    recipient_ip[0]="172.16.91.213";
    recipient_ip[1]="172.16.90.230";

    sockfd=socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&saddr, sizeof(saddr));
    saddr.sin_family=AF_INET;
    saddr.sin_port=htons(22000);
    

    for(int i=0; i<2; i++)
    {
        saddr.sin_addr.s_addr=inet_addr(recipient_ip[i]);

        bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));

        for(;;)
        {
            bzero(sendline, 100);
            fgets(sendline, 100, stdin);
            sendto(sockfd, sendline, 100, 0, (struct sockaddr*)&saddr, sizeof(saddr));
        }
    }
}