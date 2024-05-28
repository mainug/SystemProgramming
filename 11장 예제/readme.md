# 11장 예제

## fork1.c

```c
#include <stdio.h>
#include <unistd.h>

/* 자식 프로세스를생성한다. */
int main()
{
    int pid;
    printf("[%d] 프로세스 시작 \n", getpid());
    pid = fork();
    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
}
```

![Untitled](https://github.com/mainug/SystemProgramming/assets/48702167/2d3b9bf2-8dfc-4ccc-a8f0-4f28570f1167)


## fork2.c

```c
#include <stdio.h>
#include <unistd.h>

/* 부모 프로세스가자식프로세스를생성하고서로다른메시지를프린트한다. */
int main()
{
    int pid;

    pid = fork();
    if (pid == 0)
    { // 자식 프로세스
        printf("[Child] : Hello, world pid=%d\n", getpid());
    }
    else
    { // 부모 프로세스
        printf("[Parent] : Hello, world pid=%d\n", getpid());
    }
}
```

![Untitled 1](https://github.com/mainug/SystemProgramming/assets/48702167/6c584cb8-d937-4b43-9f7b-9d91a22df205)


## forkWait.c

```c
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
```

![Untitled 2](https://github.com/mainug/SystemProgramming/assets/48702167/8d3fda63-93d2-4a10-9275-730f7f8f20fe)


## waitPid.c

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 부모프로세스가자식프로세스를생성하고끝나기를기다린다. */
int main()
{
    int pid1, pid2, child, status;
    printf("[%d] 부모 프로세스 시작\n", getpid());
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("[%d] 자식 프로세스 #1 시작\n", getpid());
        sleep(1);
        printf("[%d] 자식 프로세스 #1 종료\n", getpid());
        exit(1);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        printf("[%d] 자식 프로세스 #2 시작\n", getpid());
        sleep(2);
        printf("[%d] 자식 프로세스 #2 종료\n", getpid());
        exit(2);
    }
    child = waitpid(pid1, &status, 0); // 자식프로세스#1의종료를기다린다.
    printf("[%d] 자식 프로세스 #1 %d 종료\n", getpid(), child);
    printf("\t종료 코드 %d\n", status >> 8);
}
```

![Untitled 3](https://github.com/mainug/SystemProgramming/assets/48702167/24433418-9625-48b1-b9e2-cefb62df788b)


## exec1.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 자식 프로세스를생성하여echo 명령어를실행한다. */
int main()
{
    printf("부모 프로세스 시작\n");
    if (fork() == 0)
    {
        execl("/bin/echo", "echo", "hello", NULL);
        fprintf(stderr, "첫 번째 실패");
        exit(1);
    }
    printf("부모 프로세스 끝\n");
}
```

![Untitled 4](https://github.com/mainug/SystemProgramming/assets/48702167/5a7f16d0-f801-4974-bf8c-b7a3509ec27e)


## exec2.c

```c
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
```

![Untitled 5](https://github.com/mainug/SystemProgramming/assets/48702167/b89ce223-fb44-4d6c-b525-52a105ee1776)


## exec3.c

```c
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
```

![Untitled 6](https://github.com/mainug/SystemProgramming/assets/48702167/b658b41d-f0be-40d6-8769-2c10af103c44)


## systemTest.c

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    system("pstree");
    system("ls -l");
    printf("system() 함수는 쉘 명령을 수행할 수 있습니다.\n");
    exit(0);
}
```

![Untitled 7](https://github.com/mainug/SystemProgramming/assets/48702167/9550f849-1e0a-4175-8c80-cfbcc761c2e3)


system 내에 있는 쉘 명령을 수행하는 모습

## system.c

```c
#include <sys/types.h> /* system.c*/
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int mysystem(const char *cmdstring)
{
    pid_t pid;
    int status;
    if (cmdstring == NULL) /* 명령어가NULL인경우*/
        return (1);
    if ((pid = fork()) < 0)
    {
        status = -1; /* 프로세스생성실패*/
    }
    else if (pid == 0)
    { /* 자식프로세스*/
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127); /* execl오류*/
    }
    else
    { /* 부모프로세스*/
        while (waitpid(pid, &status, 0) < 0)
            if (errno != EINTR)
            {
                status = -1; /* waitpid()로부터EINTR외의오류*/
                break;
            }
    }
    return (status);
}
```

## systemCall.c

```c
#include <sys/wait.h>
#include <stdio.h>

int main()
{
    int status;
    if ((status = system("date")) < 0)
        perror("mysystem() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));

    if ((status = system("hello")) < 0)
        perror("mysystem() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));

    if ((status = system("who; exit 44")) < 0)
        perror("mysystem() 오류");
    printf("종료코드 %d\n", WEXITSTATUS(status));
}
```

![Untitled 8](https://github.com/mainug/SystemProgramming/assets/48702167/de8be751-0183-4ccb-b9bf-75986413ceff)
