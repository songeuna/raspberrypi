#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
static int count = 0;
static pthread_mutex_t countlock = PTHREAD_MUTEX_INITIALIZER;

void *increment(void* data)
{
    int error;

    while(1){
    if(error = pthread_mutex_lock(&countlock))
	//return error;
	exit(1);
    count ++;
    pthread_mutex_unlock(&countlock);
    usleep(10);
    }
}

void *decrement(void* data)
{
    int error;

    while(1){
    if(error = pthread_mutex_lock(&countlock))
	//return error;
	exit(1);
    count --;
    pthread_mutex_unlock(&countlock);
    usleep(10);
    }
}


void *getcount(void *data)
{
    int error;
    
    while(1){
    if(error = pthread_mutex_lock(&countlock))
	//return error;
	exit(1);
    printf("%d\n",count);
       
    pthread_mutex_unlock(&countlock);
    sleep(1);
    }
}

int main(int argc, char *argv[]) 
{
    int error;
    pthread_t p_thread[3];

    if((error = pthread_create(&p_thread[0],NULL,increment,NULL)) < 0)
    {
	perror("thread create error : ");
	exit(1);
    }

    if((error = pthread_create(&p_thread[1],NULL,decrement,NULL)) < 0)
    {
	perror("thread create error : ");
	exit(1);
    }

    if((error = pthread_create(&p_thread[2],NULL,getcount,NULL)) < 0)
    {
	perror("thread create error : ");
	exit(1);
    }

    error = pthread_detach(p_thread[0]);
    error = pthread_detach(p_thread[1]);
    error = pthread_detach(p_thread[2]);

    while(1);

    return 0;
}
