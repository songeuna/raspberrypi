#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

void sigHandler(int sig)
{
	static int count = 0;
	printf("sig : %d, count : %d\n",sig, count);
	count++;

}

int main(int argc, char *argv[])
{
	pid_t pid;
	int fd, byteCount;
	char buffer[10];

	printf("%d\n",getpid());
	//memset(buffer,0,10);

	// 시그널 핸들러 등록
	signal(SIGINT, sigHandler);
	
	pause();

	fd = open("./test.txt", O_RDONLY);
	
	byteCount = read(fd, buffer, sizeof(buffer));//if file read error, return 0
	
	close(fd);

//	printf("%d\n",byteCount);

	if(byteCount == 0)
		printf("file read error\n");

	pid = atoi(buffer);
	
	//printf("sigGen1 signal proc : %d\n",pid);

//	pause();

	//kill(pid,SIGINT);
	

	for(int i = 0; i < 4; i++)
	{
		sleep(1);
		kill(pid, SIGINT);//1
		pause();
	}
	sleep(1);
	kill(pid, SIGINT);
	return 0;
}
