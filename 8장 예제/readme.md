# 8장 예제

## rdlock.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
#define START_ID 1401001

/* 잠금을이용한학생데이터베이스질의프로그램*/
int main(int argc, char *argv[])
{
    int fd, id;
    struct student record;
    struct flock lock;
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
    printf("\n검색할 학생의 학번 입력:");
    while (scanf("%d", &id) == 1)
    {
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id - START_ID) * sizeof(record);
        lock.l_len = sizeof(record);
        if (fcntl(fd, F_SETLKW, &lock) == -1)
        { /* 읽기잠금*/
            perror(argv[1]);
            exit(3);
        }
        lseek(fd, (id - START_ID) * sizeof(record), SEEK_SET);
        if ((read(fd, (char *)&record, sizeof(record)) > 0) &&
            (record.id != 0))
            printf("이름:%s\t 학번:%d\t 점수:%d\n",
                   record.name, record.id, record.score);
        else
            printf("레코드 %d 없음\n", id);
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock); /* 잠금해제*/
        printf("\n검색할 학생의 학번 입력:");
    }
    close(fd);
    exit(0);
}
```

![Untitled](https://github.com/mainug/SystemProgramming/assets/48702167/60e537c4-7170-496b-9570-f0e4c83d9410)


## wrlock.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
#define START_ID 1401001

/* 잠금을이용한학생데이터베이스수정프로그램*/
int main(int argc, char *argv[])
{
    int fd, id;
    struct student record;
    struct flock lock;
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
    printf("\n수정할 학생의 학번 입력:");
    while (scanf("%d", &id) == 1)
    {
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = (id - START_ID) * sizeof(record);
        lock.l_len = sizeof(record);
        if (fcntl(fd, F_SETLKW, &lock) == -1)
        { /* 쓰기잠금*/
            perror(argv[1]);
            exit(3);
        }
        lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);
        if ((read(fd, (char *)&record, sizeof(record)) > 0) &&
            (record.id != 0))
            printf("이름:%s\t 학번:%d\t 점수:%d\n",
                   record.name, record.id, record.score);
        else
            printf("레코드 %d 없음\n", id);
        printf("새로운 점수: ");
        scanf("%d", &record.score);
        lseek(fd, (long)-sizeof(record), SEEK_CUR);
        write(fd, (char *)&record, sizeof(record));
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock); /* 잠금해제*/
        printf("\n수정할 학생의 학번 입력:");
    }
    close(fd);
    exit(0);
}
```

![Untitled 1](https://github.com/mainug/SystemProgramming/assets/48702167/d1d4a24f-9e8c-46b1-9ea9-b57c1aa59418)


## wrlockf.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"
#define START_ID 1201001

/* 잠금을이용한학생데이터베이스수정프로그램*/
int main(int argc, char *argv[])
{
    int fd, id;
    struct student record;
    if (argc < 2)
    {
        fprintf(stderr, "사용법: %sfile\n", argv[0]);
        exit(1);
    }
    if ((fd = open(argv[1], O_RDWR)) == -1)
    {
        perror(argv[1]);
        exit(2);
    }
    printf("\n수정할학생의학번입력:");
    while (scanf("%d", &id) == 1)
    {
        lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);
        if (lockf(fd, F_LOCK, sizeof(record)) == -1)
        { /* 쓰기잠금*/
            perror(argv[1]);
            exit(3);
        }
        if ((read(fd, (char *)&record, sizeof(record)) > 0) &&
            (record.id != 0))
            printf("이름:%s\t 학번:%d\t 점수:%d\n",
                   record.name, record.id, record.score);
        else
            printf("레코드%d 없음\n", id);
        printf("새로운점수: ");
        scanf("%d", &record.score);
        lseek(fd, (long)-sizeof(record), SEEK_CUR);
        write(fd, (char *)&record, sizeof(record));
        lseek(fd, (long)(id - START_ID) * sizeof(record), SEEK_SET);
        lockf(fd, F_ULOCK, sizeof(record)); /* 잠금해제*/
        printf("\n수정할학생의학번입력:");
    }
    close(fd);
    exit(0);
}
```

![Untitled 2](https://github.com/mainug/SystemProgramming/assets/48702167/1794dd67-426e-42f1-8703-45313e2a4e37)


## file_lock.c

```c
#include <stdio.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    static struct flock lock;
    int fd, ret, c;
    if (argc < 2)
    {
        fprintf(stderr, "사용법: %s 파일\n", argv[0]);
        exit(1);
    }
    fd = open(argv[1], O_WRONLY);
    if (fd == -1)
    {
        printf("파일열기실패\n");
        exit(1);
    }
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();
    ret = fcntl(fd, F_SETLKW, &lock);
    if (ret == 0)
    { // 파일잠금성공하면
        c = getchar();
    }
}
```
