#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 명령줄인수로받은명령을실행시킨다. */
int main(int argc, char *argv[])
{
    int child, pid, status;
    pid = fork();
    if (pid == 0)
    { // 자식프로세스
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s:실행불가\n", argv[1]);
    }
    else
    { // 부모프로세스
        child = wait(&status);
        printf("[%d] 자식프로세스%d 종료\n", getpid(), pid);
        printf("\t종료코드%d \n", status >> 8);
    }
}
