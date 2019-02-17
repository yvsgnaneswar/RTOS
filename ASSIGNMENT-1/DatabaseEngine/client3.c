// client 3
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <time.h>
int main()
{
	
	clock_t t;
	int msgid, msgid1, size;
	key_t key,key1;
	struct msg{
		long int mtype;
		char message[80];
	}mq,mq1;
	
	key=ftok("key",'a');
	msgid=msgget(key,IPC_CREAT|0666);
	key1=ftok("key",'b');
	msgid1=msgget(key1,IPC_CREAT|0666);
	mq.mtype=3;
	while(1)
	{
		printf("enter the message text: ");
		scanf(" %[^\n]",mq.message);
		size=strlen(mq.message);
		msgsnd(msgid,&mq,size+1,0);
		t = clock();
		msgrcv(msgid1,&mq1,sizeof(mq1.message),3,0);
		t = clock()-t;
		//printf("message type: %ld",mq1.mtype);
		printf("message text: %s\n",mq1.message);
		printf("Time taken for servicing request: %f\n",((double)t)/CLOCKS_PER_SEC );
		//msgctl(msgid1, IPC_RMID, NULL);
	}
}
