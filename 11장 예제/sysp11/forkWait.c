#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 부모프로세스가자식프로세스를생성하고끝나기를기다린다. */
int main()
{
    int pid, child, status;

    printf("[%d] 부모 프로세스 시작\n", getpid());
    pid = fork();
    if (pid == 0)
    {
        printf("[%d] 자식 프로세스 시작\n", getpid());
        exit(1);
    }
    child = wait(&status); // 자식프로세스가끝나기를기다린다.
    printf("[%d] 자식 프로세스 %d 종료\n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);
}
