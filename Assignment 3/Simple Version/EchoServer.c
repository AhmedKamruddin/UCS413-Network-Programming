#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>

int main()
{
	char str[100];
	char sendline[100];
	char recvline[100];
	int listen_fd, comm_fd;
	struct sockaddr_in servaddr;
	listen_fd=socket(AF_INET, SOCK_STREAM, 0);
	
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(22000);

	bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listen_fd, 10);

	comm_fd=accept(listen_fd, (struct sockaddr*) NULL, NULL);
		
	while(1)
	{
		bzero(str, 100);

		recv(comm_fd, str, 100, 0);

		printf("%s", str);
		
		send(comm_fd, str, strlen(str), 0);

		bzero(sendline, 100);
		bzero(recvline, 100);
        fgets(sendline, 100, stdin); //stdin=0 for standard input
		send(comm_fd, sendline, strlen(sendline), 0);
		//printf("Message sent\n");
		recv(comm_fd, recvline, 100, 0);
		//printf("Message Acknowledged\n");

		//close(comm_fd);
		
	}

}
