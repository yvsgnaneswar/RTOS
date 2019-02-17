#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <fcntl.h>


int main()
{
	
	
	int msgid, msgid1, size,size1;
	key_t key,key1;
	struct msg{
		long int mtype;
		char message[80];
	}mq,mq1;
	
	char * split_text;
	int fd_read;
	char resp[200];
	key=ftok("key",'a');
	msgid=msgget(key,IPC_CREAT|0666);
	key1=ftok("key",'b');
	msgid1=msgget(key1,IPC_CREAT|0666);
	//printf("enter the message type to receive: ");
	//scanf("%ld",&mq.mtype);
	while(1)
	{
		msgrcv(msgid,&mq,sizeof(mq.message),0,0);
		//msgrcv(msgid,&mq,sizeof(mq.message),mq.mtype,0);
		printf("message type: %ld",mq.mtype);
		printf("message text: %s\n",mq.message);

		split_text = strtok (mq.message," ,.-");

		if(strcmp(split_text,"GET")==0)
		{
		  	/**Extracting file name **/
		  	split_text = strtok (NULL," ,-");
			fd_read=open(split_text,O_RDONLY);
			if(fd_read>=0)
			{
				read(fd_read,&resp,200);
				close(fd_read);
				strcpy(mq1.message,resp);
				//return 0;
			}
			else
			{
				strcpy(mq1.message,"data not found");
			}
		}
		else
		{
		  	strcpy(mq1.message,"invalid");
		}
		mq1.mtype=mq.mtype;
		size1=strlen(mq1.message);
		msgsnd(msgid1,&mq1,size1+1,0);
	}
}
