# 10장 예제

## args.c

```c
#include <stdio.h>
#include <stdlib.h>

/* 모든 명령줄 인수를출력한다. */
int main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < argc; i++) /* 모든 명령줄 인수출력 */
        printf("argv[%d]: %s \n", i, argv[i]);

    exit(0);
}
```

![Untitled](https://github.com/mainug/SystemProgramming/assets/48702167/2952ede0-b70f-4150-afba-581fd80b84a3)


실행 명령 문장 자체도 argv배열의 가장 앞에 들어가는 것을 알 수 있음

## environ.c

```c
#include <stdio.h>
#include <stdlib.h>

/* 모든 환경 변수를출력한다. */
int main(int argc, char *argv[])
{
    char **ptr;
    extern char **environ;

    for (ptr = environ; *ptr != 0; ptr++) /* 모든 환경 변수 값 출력*/
        printf("%s \n", *ptr);

    exit(0);
}
```

![Untitled 1](https://github.com/mainug/SystemProgramming/assets/48702167/04a2fd31-f56f-41e0-99ec-758d38bca132)


![Untitled 2](https://github.com/mainug/SystemProgramming/assets/48702167/c689671f-2f78-455d-bca0-0609f09b1b71)


이외의 다른 환경 변수 값도 출력

## printenv.c

```c
#include <stdio.h>
#include <stdlib.h>

/* 환경 변수를 3개 프린트한다. */
int main(int argc, char *argv[])
{
    char *ptr;

    ptr = getenv("HOME");
    printf("HOME = %s \n", ptr);

    ptr = getenv("SHELL");
    printf("SHELL = %s \n", ptr);

    ptr = getenv("PATH");
    printf("PATH = %s \n", ptr);

    exit(0);
}
```

![Untitled 3](https://github.com/mainug/SystemProgramming/assets/48702167/e2d0f793-1313-4a86-b380-c3c782f6202c)


환경 변수 3개 HOME, SHELL, PATH가 출력 됨

## pid.c

```c
#include <stdio.h>

/* 프로세스 번호를출력한다. */
int main()
{
    int pid;
    printf("나의 프로세스 번호 : %d \n", getpid());
    printf("내 부모 프로세스 번호 : %d \n", getppid());
}
```

![Untitled 4](https://github.com/mainug/SystemProgramming/assets/48702167/251c2650-d359-4542-9c3b-0a126e9da0c8)


## uid.c

```c
#include <stdio.h>
#include <pwd.h>
#include <grp.h>

/* 사용자 ID를 출력한다. */
int main()
{
    int pid;
    printf("나의 실제 사용자 ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
    printf("나의 유효 사용자 ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
    printf("나의 실제 그룹 ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
    printf("나의 유효 그룹 ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
}
```

![Untitled 5](https://github.com/mainug/SystemProgramming/assets/48702167/17da6d00-a30d-48d3-99e0-10f073c36343)

