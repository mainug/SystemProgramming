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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled.png)

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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled%201.png)

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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled%202.png)

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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled%203.png)

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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled%204.png)

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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled%205.png)

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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled%206.png)

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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled%207.png)

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

![Untitled](11%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2097d60cd9e3114680aec17e083cee14dd/Untitled%208.png)