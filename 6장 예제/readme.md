# 6장 예제

## fopen.c

```c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char *argv[])
{
    int fd;
    if ((fd = open(argv[1], O_RDWR)) == -1)
        printf("파일열기오류\n");
    else
        printf("파일%s 열기성공: %d\n", argv[1], fd);
    close(fd);
    exit(0);
}
```

![Untitled](6%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%20556042441baf497fac52db76c134e18e/Untitled.png)

## fsize.c

```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFSIZE 512

/* 파일크기를계산한다*/
int main(int argc, char *argv[])
{
    char buffer[BUFSIZE];
    int fd;
    ssize_t nread;
    long total = 0;
    if ((fd = open(argv[1], O_RDONLY)) == -1)
        perror(argv[1]);
    /* 파일의끝에도달할때까지반복해서읽으면서파일크기계산*/
    while ((nread = read(fd, buffer, BUFSIZE)) > 0)
        total += nread;
    close(fd);
    printf("%s 파일크기: %ld바이트\n", argv[1], total);
    exit(0);
}
```

![Untitled](6%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%20556042441baf497fac52db76c134e18e/Untitled%201.png)

## copy.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/* 파일복사프로그램*/
int main(int argc, char *argv[])
{
    int fd1, fd2, n;
    char buf[BUFSIZ];
    if (argc != 3)
    {
        fprintf(stderr, "사용법: %s file1 file2\n",
                argv[0]);
        exit(1);
    }
    if ((fd1 = open(argv[1], O_RDONLY)) ==
        1)
    {
        perror(argv[1]);
        exit(2);
    }
    if ((fd2 = open(argv[2], O_WRONLY |
                                 O_CREAT | O_TRUNC 0644)) == -1)
    {
        perror(argv[2]);
        exit(3);
    }
    while ((n = read(fd1, buf, BUFSIZ)) > 0)
        write(fd2, buf, n); // 읽은내용을쓴다.
    exit(0);
}
```

## student.h

```c
#define MAX 24
#define START_ID 1401001

struct student
{
    char name[MAX];
    int id;
    int score;
};
```

## dbcreate.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 학생정보를입력받아데이터베이스파일에저장한다. */
int main(int argc, char *argv[])
{
    int fd;
    struct student record;
    if (argc < 2)
    {
        fprintf(stderr, "사용법: %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) == -1)
    {
        perror(argv[1]);
        exit(2);
    }
    printf("%-9s %-8s %-4s\n", "학번", "이름", "점수");
    while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3)
    {
        lseek(fd, (record.id - START_ID) * sizeof(record), SEEK_SET);
        write(fd, (char *)&record, sizeof(record));
    }
    close(fd);
    exit(0);
}
```

## dbquery.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 학번을입력받아해당학생의레코드를파일에서읽어출력한다. */
int main(int argc, char *argv[])
{
    int fd, id;
    struct student record;
    if (argc < 2)
    {
        fprintf(stderr, "사용법: %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        perror(argv[1]);
        exit(2);
    }
    do
    {
        printf("\n검색할학생의학번입력:");
        if (scanf("%d", &id) == 1)
        {
            lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET);
            if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0))
                printf("이름:%s\t 학번:%d\t 점수:%d\n", record.name, record.id,
                       record.score);
            else
                printf("레코드%d 없음\n", id);
        }
        else
            printf(“입력오류”);
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y');
    close(fd);
    exit(0);
}
```

## dbupdate.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"

/* 학번을입력받아해당학생레코드를수정한다. */
int main(int argc, char *argv[])
{
    int fd, id;
    char c;
    struct student record;
    if (argc < 2)
    {
        fprintf(stderr, "사용법: %s file\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDWR)) == -1)
    {
        perror(argv[1]);
        exit(2);
    }
    do
    {
        printf("수정할학생의학번입력: ");
        if (scanf("%d", &id) == 1)
        {
            lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);
            if ((read(fd, (char *)&record, sizeof(record)) > 0) && (record.id != 0))
            {
                printf("학번:%8d\t 이름:%4s\t 점수:%4d\n",
                       record.id, record.name, record.score);
                printf("새로운점수: ");
                scanf("%d", &record.score);
                lseek(fd, (long)-sizeof(record), SEEK_CUR);
                write(fd, (char *)&record, sizeof(record));
            }
            else
                printf("레코드%d 없음\n", id);
        }
        else
            printf("입력오류\n");
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y');
    close(fd);
    exit(0);
}
```