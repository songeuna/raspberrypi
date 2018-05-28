#include<time.h>
#include<sys/time.h>
#include<stdlib.h>

int main()int argc, char **argv)
{
    int i, j;
    time_t UTCtime;
    struct tm *tm;
    char buf[BUFSIZ];
    struct timeval UTCtime_u;

    time(&TUCtime); //UTC 현재 시간 구하기
    printf("time : %u\n", (unsigned)UTCtime); //UTC 현재 시간출력

    gettimeofdat(&UTCtime_u, NULL); //UTC 현재 시간 구하기(마이크로초까지)
    printf("gettimeofdat : %ld/%d\n",UTCtime_u.tv_sec, UTCtime_u.tv_usec);
}
