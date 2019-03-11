#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main()
{
	int server_desc, client_desc, val;
	struct sockaddr_in server,client;
	char message[200];
  int opt = 1;
  int addrlen = sizeof(client);

	server_desc = socket(AF_INET,SOCK_STREAM,0);
	printf("socket created\n");

  if (setsockopt(server_desc, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=htons(8000);
  memset(server.sin_zero, '\0', sizeof server.sin_zero);

  int bind_check = bind(server_desc, (struct sockaddr *)&server, sizeof(server));
  printf("Bind check = %d\n", bind_check);
  listen(server_desc, 5);

  while(1)
  {
    client_desc = accept(server_desc, (struct sockaddr *)&client, (socklen_t*)&addrlen);
    if(fork()==0)
    {
  	  while((val=read(client_desc, message, sizeof(message)))>0)
      {
  		  if (message[0] >= 'A' && message[0] <= 'Z')
          message[0] = message[0] + 32;
        else if (message[0] >= 'a' && message[0] <= 'z')
          message[0] = message[0] - 32;
  		  send(client_desc, message, val, 0);
      }
    }
  }
}
