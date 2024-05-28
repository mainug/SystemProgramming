#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 세개의자식프로세스를생성하여각각다른명령어를실행한다. */
int main()
{
    printf("부모프로세스시작\n");
    if (fork() == 0)
    {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "첫번째실패");
        exit(1);
    }
    if (fork() == 0)
    {
        execl("/bin/date", "date", NULL);
        fprintf(stderr, "두번째실패");
        exit(2);
    }
    if (fork() == 0)
    {
        execl("/bin/ls", "ls", "-l", NULL);
        fprintf(stderr, "세번째실패");
        exit(3);
    }
    printf("부모프로세스끝\n");
}
