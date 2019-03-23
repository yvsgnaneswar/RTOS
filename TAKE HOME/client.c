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
#include <signal.h> 
FILE *fp;
void sigintHandler(int sig_num) 
{ 
    //signal(SIGINT, sigintHandler); 
    printf("\n exiting \n"); 
    fclose(fp);
    exit(0);
} 

int main()
{

	time_t mytime;
    char * time_str;
	//FILE *fp;
	fp=fopen("data.csv","w+");
	clock_t t;
	int client_desc, val,i;
	struct sockaddr_in server;
    char message[200];
    char *m1;
    fprintf(fp,"Time,Sensor1,Sensor2,Sensor3,Sensor4,Sensor5");
    //fclose(fp);
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
    	signal(SIGINT, sigintHandler);
    	mytime = time(NULL);
    	time_str = ctime(&mytime); 
    	time_str[strlen(time_str)-1] = '\0';
    	fprintf(fp,"\n%s", time_str);
    	//fprintf(fp, "\n%lu", (unsigned long)time(NULL));
    	//scanf(" %[^\n]",message);
    	memset(message,0,strlen(message));
    	m1="GET";
    	strcpy(message,m1);
    	printf("%s",message);
		if(send(client_desc, message,sizeof(message), 0)>0)
		{   
			sleep(2);	
			for(i=1;i<6;i++)
			{
				val = recv(client_desc, message, 200, 0);
				//t = clock()-t;
				//if(i==1)
				//	fprintf(fp,"\n%s",message);
				//else
				fprintf(fp,",%s",message);
				if(val<=0)
				{
					printf("Nothing received\n");
				}
				else
				{
					printf("%s\n",message );
				}
				//printf("Time taken for servicing request: %f\n",((double)t)/CLOCKS_PER_SEC );
			}
		}
	}
}
