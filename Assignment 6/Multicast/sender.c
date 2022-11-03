#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

struct pass_parameters
{
    int sockfd;
    char *ip;
    char sendline[100];
};

void *send_message(void *context)
{   
    pid_t childpid=fork();

    if(childpid==0)
    {
        struct pass_parameters *pp=context;
        struct sockaddr_in saddr;

        bzero(&saddr, sizeof(saddr));
        saddr.sin_family=AF_INET;
        saddr.sin_port=htons(22000);
        saddr.sin_addr.s_addr=inet_addr(pp->ip);

        bind(pp->sockfd, (struct sockaddr*)&saddr, sizeof(saddr));

        sendto(pp->sockfd, pp->sendline, 100, 0, (struct sockaddr*)&saddr, sizeof(saddr));
        
        exit(0);
    }
}

int main()
{
    int n=2;
    int sockfd;
    pthread_t thread_send_id;
    struct pass_parameters pp;
    char sendline[100];    
    char *recipient_ip[n];
    recipient_ip[0]="192.168.122.125";
    recipient_ip[1]="192.168.122.142";

    sockfd=socket(AF_INET, SOCK_DGRAM, 0);

    bzero(sendline, sizeof(sendline));
    fgets(sendline, 100, stdin);
    strcpy(pp.sendline, sendline);
    pp.sockfd=sockfd;
    for(int i=0; i<n; i++)
    {
        pp.ip=recipient_ip[i];
        if(pthread_create(&thread_send_id, NULL, send_message, &pp))
        {
            fprintf(stderr, "Failed to create thread\n");
            return EXIT_FAILURE;
        }
        pthread_join(thread_send_id, NULL);
    }
}
