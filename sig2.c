#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int fd, byteCount;
	
	printf("%d\n",getpid());
	//memset(buffer,0,10);

	// 시그널 핸들러 등록
	signal(SIGINT, sigHandler);
	
	pause();

	
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
