/*The sender program is very similar to msg1.c. In the main set up, delete the msg_to_receive declaration and replace it with buffer[BUFSIZ], remove the message queue delete and make the following changes to the running loop. We now have a call to msgsnd to send the entered text to the queue. */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct my_msg_st {
	long int my_msg_type;
	char name[100];
	int age;
	int id;
	char some_text[10];
};

int main()
{
	int running = 1;
	struct my_msg_st some_data;
	int msgid;
	char buffer[BUFSIZ];

	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);//메세지큐 생성

	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}

	while(running)
	{
		printf("Enter name: ");
		scanf("%s",&some_data.name);

		printf("Enter age: ");
		scanf("%d",&some_data.age);

		printf("Enter id: ");
		scanf("%d",&some_data.id);	

		printf("Continue? yes/no : ");
		scanf("%s", &some_data.some_text);

		if(msgsnd(msgid, (void *)&some_data, sizeof(some_data), 0) == -1)
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}

		if(strncmp(some_data.some_text, "no", 2) == 0)
		{
			
			running = 0;
		}

	}

	exit(EXIT_SUCCESS);
}
