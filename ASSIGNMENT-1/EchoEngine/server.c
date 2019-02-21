#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
int main()
{
	
	int msgid, msgid1, size,size1;
	key_t key,key1;
	struct msg{
		long int mtype;
		char message[80];
	}mq,mq1;
	


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
		//msgctl(msgid, IPC_RMID, NULL);
		

		if (mq.message[0] >= 'A' && mq.message[0] <= 'Z')
	        mq.message[0] = mq.message[0] + 32;
	    else if (mq.message[0] >= 'a' && mq.message[0] <= 'z')
	        mq.message[0] = mq.message[0] - 32;

		size1=strlen(mq.message);
		msgsnd(msgid1,&mq,size1+1,0);
	}
	
}
