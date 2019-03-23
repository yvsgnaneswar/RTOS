#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <pthread.h>
#include <semaphore.h>

pthread_cond_t cond1  =  
               PTHREAD_COND_INITIALIZER; 
pthread_cond_t cond2  =  
               PTHREAD_COND_INITIALIZER; 
pthread_cond_t cond3  =  
               PTHREAD_COND_INITIALIZER;
pthread_cond_t cond4  =  
               PTHREAD_COND_INITIALIZER;
pthread_cond_t cond5  =  
               PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock4 = PTHREAD_MUTEX_INITIALIZER;
struct timeval start, stop;
void * player1(void *n){
	while(1){
		static int move = 0;
		static int state = 0;

		pthread_mutex_lock(&lock1); 
		pthread_cond_wait(&cond1, &lock1);
		int dice;
		if(move<100){
			dice = rand() % 6 + 1;
			if(move+dice<=100)
				move = move + dice;
			printf("player 1 %d\n",move);
		}

		if(move>=100){
			gettimeofday(&stop, NULL);
			printf("player1 wins\n");
			printf("time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&cond5);  
        pthread_mutex_unlock(&lock1);

	}
	return NULL;
}

void * player2(void *n){
	while(1){
		static int move = 0;
		static int state = 0;

		pthread_mutex_lock(&lock2); 
		pthread_cond_wait(&cond2, &lock2);
		int dice;
		if(move<100){
			dice = rand() % 6 + 1;
			if(move+dice<=100)
				move = move + dice;
			printf("player 2 %d\n",move);
		}

		if(move>=100){
			gettimeofday(&stop, NULL);
			printf("player2 wins\n");
			printf("time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&cond5);  
        pthread_mutex_unlock(&lock2);

	}
	return NULL;
}

void * player3(void *n){
	while(1){
		static int move = 0;
		static int state = 0;

		pthread_mutex_lock(&lock3); 
		pthread_cond_wait(&cond3, &lock3);
		int dice;
		if(move<100){
			dice = rand() % 6 + 1;
			if(move+dice<=100)
				move = move + dice;
			printf("player 3 %d\n",move);
		}

		if(move>=100){
			gettimeofday(&stop, NULL);
			printf("player3 wins\n");
			printf("time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&cond5);  
        pthread_mutex_unlock(&lock3);

	}
	return NULL;
}

void * player4(void *n){
	while(1){
		static int move = 0;
		static int state = 0;

		pthread_mutex_lock(&lock4); 
		pthread_cond_wait(&cond4, &lock4);
		int dice;
		if(move<100){
			dice = rand() % 6 + 1;
			if(move+dice<=100)
				move = move + dice;
			printf("player 4 %d\n",move);
		}

		if(move>=100){
			gettimeofday(&stop, NULL);
			printf("player4 wins\n");
			printf("time taken to win (micro seconds) %lu\n", (stop.tv_sec - start.tv_sec)*1000000 + (stop.tv_usec - start.tv_usec));
			exit(0);
		}
        pthread_cond_signal(&cond5); 
        pthread_mutex_unlock(&lock4);

	}
	return NULL;
}

int main(){
	pthread_t  tid1, tid2, tid3, tid4; 
    int n1 = 1, n2 = 2, n3 = 3, n4 = 4;
    srand(time(0));
    pthread_create(&tid1, NULL, player1, (void *)&n1); 
    pthread_create(&tid2, NULL, player2, (void *)&n2); 
    pthread_create(&tid3, NULL, player3, (void *)&n3); 
    pthread_create(&tid4, NULL, player4, (void *)&n4); 
    gettimeofday(&start, NULL);
     
    while(1)
    {
    	//pthread_mutex_unlock(&lock1);
    	pthread_cond_signal(&cond1);
    	pthread_mutex_unlock(&lock1);
    	pthread_mutex_lock(&lock1);
    	pthread_cond_wait(&cond5, &lock1);
    	//pthread_mutex_lock(&lock1);

    	//pthread_mutex_unlock(&lock2);
    	pthread_cond_signal(&cond2);
    	pthread_mutex_unlock(&lock2);
    	pthread_mutex_lock(&lock2);
    	pthread_cond_wait(&cond5, &lock2);
    	//pthread_mutex_lock(&lock2);

    	//pthread_mutex_unlock(&lock3);
    	pthread_cond_signal(&cond3);
    	pthread_mutex_unlock(&lock3);
    	pthread_mutex_lock(&lock3);
    	pthread_cond_wait(&cond5, &lock3);
    	//pthread_mutex_lock(&lock3);

    	//pthread_mutex_unlock(&lock4);
    	pthread_cond_signal(&cond4);
    	pthread_mutex_unlock(&lock4);
    	pthread_mutex_lock(&lock4);
    	pthread_cond_wait(&cond5, &lock4);
    	//pthread_mutex_lock(&lock4);
    }
}
