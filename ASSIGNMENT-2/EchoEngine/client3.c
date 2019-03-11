#include <sys/types.h>         
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <arpa/inet.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	clock_t t;
	int client_desc, val;
	struct sockaddr_in server;
    char message[200];

    client_desc = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(8000);
	memset(server.sin_zero, '\0', sizeof server.sin_zero);

	if (connect(client_desc,(struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    while(1)
    {
    	scanf(" %[^\n]",message);
		if(send(client_desc, message,strlen(message), 0)>0)
		{
			t = clock();
			val = recv(client_desc, message, 200, 0);
			t = clock()-t;
			if(val<=0)
			{
				printf("Nothing received\n");
			}
			else
			{
				printf("%s\n",message );
			}
			printf("Time taken for servicing request: %f\n",((double)t)/CLOCKS_PER_SEC );
		}
	}
}
