#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<limits.h>
#include<sys/stat.h>

#define FIFO_NAME "/tmp/fifo"
#define BUF 1024
#define BUFFER_SIZE PIPE_BUF

int main()
{
	int fd;
	int pipe_fd,res;
	int open_mode = O_RDONLY;
	char p_buffer[BUFFER_SIZE + 1];
	int bytes_write = 0;
	char buffer[BUF];

	memset(buffer,'\0',sizeof(buffer));
	memset(p_buffer,'\0',sizeof(buffer));

	printf("PIPE FILE ACCESS\n");

	if(access(FIFO_NAME,F_OK) == -1)
		printf("PIPE ACCESS ERROR\n");


 	fd = open("doc2.txt",O_RDWR | O_CREAT | O_TRUNC,\
		       	S_IRWXU | S_IWGRP | S_IRGRP | S_IROTH);

	if(fd != -1)
	{
		printf("PIPE FILE OPEN\n");
		pipe_fd = open(FIFO_NAME, open_mode);
		
		if(pipe_fd != -1)
		{
			res = read(pipe_fd,p_buffer,BUFFER_SIZE);
		//	(void)close(pipe_fd);
		}

		bytes_write = write(fd,p_buffer,strlen(p_buffer));
		printf("FILE CLOSE\n");
		(void)close(fd);
		(void)close(pipe_fd);	
	}
	else
	{
		printf("doc2.txt FILE OPEN ERROR\n");
		(void)close(fd);
		(void)close(pipe_fd);
		return 0;
	}

	return 0;



}
