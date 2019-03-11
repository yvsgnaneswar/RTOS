#include <sys/types.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdio.h>
#include "string.h"
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>


int main()
{
  char * split_text;
  int fd_read;
  char resp[200];
	int server_desc, client_desc, n;
	struct sockaddr_in server,client;
	char message[200],response[200];
  int opt = 1;
  int n_response;
  int addrlen = sizeof(client);

	server_desc = socket(AF_INET,SOCK_STREAM,0);
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
  listen(server_desc, 5);
  n_response = sizeof(response);
    
  while(1)
  {
    client_desc = accept(server_desc, (struct sockaddr *)&client, (socklen_t*)&addrlen);
    if(fork()==0)
    {
  	 while((n=read(client_desc, message, sizeof(message)))>0)
      {
        split_text = strtok (message," ,.-");
        if(strcmp(split_text,"GET")==0)
        {
          split_text = strtok (NULL," ,-");
          fd_read=open(split_text,O_RDONLY);
          if(fd_read>=0)
          {
            read(fd_read,&resp,200);
            close(fd_read);
            strcpy(response,resp);
          }
          else
          {
            strcpy(response,"data not found");
          }
        }
        else
        {
          strcpy(response,"invalid");
        }
        send(client_desc, response, n_response, 0);
      }
    }
  }
}
