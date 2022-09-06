#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdint.h>

void *receive_message(void* arg)
{
    char str[100];
    intptr_t sockfd=(intptr_t)arg;
    while(1)
    {    
        bzero(str, 100);
        recv(sockfd, str, 100, 0);            //Receive message
        
        if(strncmp(str, "exit", 4)==0)
        {
			printf("Exiting...\n");
            close(sockfd);
            exit(0);
        }
        printf("%s", str);                 
       
    }
}

void *send_message(void* arg)
{
    char str[100];
    intptr_t sockfd=(intptr_t)arg;
    while(1)
    {
        bzero(str, 100);
        fgets(str, 100, stdin);
        send(sockfd, str, strlen(str), 0);    //Send message
                
        if(strncmp(str, "exit", 4)==0)
        {
            printf("Exiting...\n");
            close(sockfd);
            exit(0);
        }
    }
}

int main(int argc, char **argv)
{
    int sockfd, n;
    char str[100];
    struct sockaddr_in servaddr;

    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(22000);
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));


    pthread_t thread_receive_id, thread_send_id;
    
    pthread_create(&thread_receive_id, NULL, receive_message, (void*)sockfd);
    pthread_create(&thread_send_id, NULL, send_message, (void*)sockfd);
    pthread_join(thread_receive_id, NULL);
    pthread_join(thread_send_id, NULL);
}