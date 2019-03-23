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
  int fd_read1;
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
  n_response = sizeof(resp);
    
  while(1)
  {
    client_desc = accept(server_desc, (struct sockaddr *)&client, (socklen_t*)&addrlen);
    if(fork()==0)
    {
      while((n=read(client_desc, message, sizeof(message)))>0)
      {
        //split_text = strtok (message," ,.-");
        printf("%s",message);
        printf("asasassa\n");
        if(strcmp(message,"GET")==0)
        {
          printf("entered\n");
          //sleep(2);
          memset(resp,0,sizeof(resp));
          fd_read1=open("sensor1.txt",O_RDONLY);
          read(fd_read1,&resp,200);
          close(fd_read1);
          send(client_desc, resp, n_response, 0);
          //strcpy(resp1,resp);
          //printf("sensor1  %s\n",resp);
          memset(resp,0,strlen(resp));
          printf("sent1\n");
          fd_read1=open("sensor2.txt",O_RDONLY);
          read(fd_read1,&resp,200);
          printf("read2\n");
          close(fd_read1);
          send(client_desc, resp, n_response, 0);
          //strcpy(resp1,resp);
          //printf("sensor2  %s\n",resp1);
          memset(resp,0,strlen(resp));
          fd_read1=open("sensor3.txt",O_RDONLY);
          read(fd_read1,&resp,200);
          close(fd_read1);
          send(client_desc, resp, n_response, 0);
          //strcpy(resp1,resp);
          //printf("sensor3  %s\n",resp1);
          memset(resp,0,strlen(resp));
          fd_read1=open("sensor4.txt",O_RDONLY);
          read(fd_read1,&resp,200);
          close(fd_read1);
          send(client_desc, resp, n_response, 0);
          //strcpy(resp1,resp);
          //printf("sensor4  %s\n",resp1);
          memset(resp,0,strlen(resp));
          fd_read1=open("sensor5.txt",O_RDONLY);
          read(fd_read1,&resp,200);
          close(fd_read1);
          send(client_desc, resp, n_response, 0);
          //strcpy(resp1,resp);
          //printf("sensor5  %s\n",resp1);
          //memset(resp,0,strlen(resp));
        }
      }
    }
  }
}
