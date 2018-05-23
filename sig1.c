#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>

void sigHandler(int sig)
{
	static int count = 0;
	int byteCount;

	byteCount = write(fd, buffer, strlen(sig));	
}
int main(int argc, char *argv[])
{
	pid_t pid;			
	int fd;
	char buffer[10];

	//시그널 핸들러 등록
	signal(SIGINT, sigHandler); //(SIGINT = 'Ctrl + C')의 입력을 기다림, 입력시 sigHandler 실행
	
	// pid값을 읽어와
	// test.txt파일에 쓰기
	pid = getpid();
	sprintf(buffer,"%d",pid);

	for(int i = 0; i < 10; i++)
	{

		fd = open("./log.txt",O_RDWR | O_CREAT,\ 
		       	S_IRWXU | S_IWGRP | S_IRGRP | S_IROTH);


		pid = atoi(argv[1]);//fd에 적힌 값은 문자이므로 atoi로 int형으로 변환
		printf("sigGen2 signal proc : %d\n", pid);

		sleep(1);
		kill(pid, SIGINT);//pid가 가르키는 프로세서로 SIGINT(Ctrl + C)가 눌린값을 전달//1
		
		pause();//signal이 들어올때까지 기다림 //2
	
	}

	close(fd);
	return 0;
}
