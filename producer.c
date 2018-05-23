#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<limits.h>

//#define BUF 1024
#define BUFFER_SIZE PIPE_BUF

#define FIFO_NAME "/tmp/fifo"

int main()
{
	int fd;
	char buffer[BUFFER_SIZE+1];
	int pipe_fd;
	int open_mode = O_RDONLY;
	char p_buffer[BUFFER_SIZE + 1];
	int res;
	int bytes_sent = 0;
	int count=0;

	memset(p_buffer,'\0',sizeof(buffer));
	memset(buffer,'\0',sizeof(buffer));

	fd = open("doc.txt", open_mode);
	printf("doc.txt FILE OPEN\n");

	if(fd != -1)
	{
		read(fd,buffer,sizeof(buffer));
		printf("FILE READ\n");
		//printf("%s\n",buffer);
		if(access(FIFO_NAME,F_OK) == -1)
		{
			res = mkfifo (FIFO_NAME, 0777);
	
			if(res != 0)
			{
				fprintf(stderr,"Could not create fifo %s\n", FIFO_NAME);
				exit(EXIT_FAILURE);
			}
		}

		pipe_fd = open(FIFO_NAME, O_WRONLY);

		if(pipe_fd != -1)
		{
			while(bytes_sent < BUFFER_SIZE)
			{
				res = write(pipe_fd,buffer,BUFFER_SIZE);
				if(res == -1)
				{
					fprintf(stderr,"Write error on pipe\n");
					exit(EXIT_FAILURE);
				}
				bytes_sent += res;
			}
	
			(void)close(pipe_fd);
			(void)close(fd);
		}
	}
	
	else 
	{
		printf("file open error\n");
		return 0;
	}
//	pipe_fd = open(FIFO_NAME, open_mode);
//	printf("FIFO OPEN\n");

	return 0;
}
