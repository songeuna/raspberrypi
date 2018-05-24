#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>


struct my_msg_st{
	long int my_msg_type;//메세지 타입은 반드시 넣어줘야함
	char name[100];
	unsigned char age;
	int id;
	char some_text[10];
};

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_receive = 0;
	int fd;
	int size;

	/* First, we set up the message queue. */

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	/* Then the messages are retrieved from the queue, until an end message is encountered.
	 * lastly, the message queue is deloete.*/

	fd = open("msg.txt",O_RDWR | O_CREAT | O_TRUNC,\
		       	S_IRWXU | S_IWGRP | S_IRGRP | S_IROTH);

	if(fd != -1)
	{
		while(running)
		{
			if(msgrcv(msgid, (void *)&some_data, sizeof(some_data), msg_to_receive, 0) == -1)
			{
				fprintf(stderr, "msgrcv failed with error: %d\n", errno);
				exit(EXIT_FAILURE);
			}

			printf("Name: %s\n", some_data.name);
			printf("Age: %d\n", some_data.age);
			printf("Id: %d\n", some_data.id);		

			write(fd,&some_data,sizeof(some_data));
		
			if(strncmp(some_data.some_text, "no", 2) == 0)
			{
				running = 0;
			}
		}
	}

	close(fd);

	if(msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	
	exit(EXIT_SUCCESS);
}

