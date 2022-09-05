#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdint.h>

struct sockaddr_in set_values()
{
    struct sockaddr_in servaddr;
    servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	servaddr.sin_port=htons(22000);

    return servaddr;
}

struct beepboop
{
    //Just to share serverStorage between receive_message() and send_message()
    struct sockaddr_storage serverStorage;
}bb;

void *receive_message(void* arg)
{
    char recvline[100];
    struct sockaddr_in servaddr=set_values();
	intptr_t sockfd=(intptr_t)arg;
    socklen_t addr_size;

    addr_size=sizeof(bb.serverStorage);

    while(1)
    {    
        bzero(recvline, 100);
        recvfrom(sockfd, recvline, 100, 0, (struct sockaddr *) &bb.serverStorage, &addr_size);
		
        if(strncmp(recvline, "exit", 4)==0)
        {
			printf("Exiting...\n");
            exit(0);
        }
        printf("%s", recvline);
    }
}

void *send_message(void* arg)
{
    char sendline[100];
    intptr_t sockfd=(intptr_t)arg;
    struct sockaddr_in servaddr=set_values();
	socklen_t addr_size;
    
    addr_size=sizeof(bb.serverStorage);
    while(1)
    {
        bzero(sendline, 100);
		fgets(sendline, 100, stdin);
		sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *) &bb.serverStorage, addr_size);

        if(strncmp(sendline, "exit", 4)==0)
        {
            printf("Exiting...\n");
            exit(0);
        }
    }
}

int main()
{
	char sendline[100];
	char recvline[100];
	int sockfd;
	struct sockaddr_in servaddr;

	sockfd=socket(AF_INET, SOCK_DGRAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr=set_values();

	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	
    printf("Wait for client to initiate communication. Type \"exit\" to exit.\n");

    pthread_t thread_receive_id, thread_send_id;
    pthread_create(&thread_receive_id, NULL, receive_message, (void*)sockfd);
    pthread_create(&thread_send_id, NULL, send_message, (void*)sockfd);
    pthread_join(thread_receive_id, NULL);
    pthread_join(thread_send_id, NULL);
}
