# 9장 예제

## test1.c

```c
#include <stdio.h>

/* 텍스트파일내용을표준출력에프린트*/
int main(int argc, char *argv[])
{
    FILE *fp;
    int c;
    if (argc < 2)
        fp = stdin; // 명령줄인수가없으면표준입력사용
    else
        fp = fopen(argv[1], "r"); // 읽기전용으로파일열기
    c = getc(fp);                 // 파일로부터문자읽기
    while (c != EOF)
    {                    // 파일끝이아니면
        putc(c, stdout); // 읽은문자를표준출력에
        c = getc(fp);    // 파일로부터문자읽기
    }
    fclose(fp);
    return 0;
}
```

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled.png)

test1.txt에 적혀있는 내용을 출력해줌

## test2.c

```c
#include <stdio.h>

/* 파일복사프로그램*/
int main(int argc, char *argv[])
{
    char c;
    FILE *fp1, *fp2;
    if (argc != 3)
    {
        fprintf(stderr, "사용법: %s 파일1 파일2\n", argv[0]);
        return 1;
    }
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL)
    {
        fprintf(stderr, "파일%s 열기오류\n", argv[1]);
        return 2;
    }
    fp2 = fopen(argv[2], "w");
    while ((c = fgetc(fp1)) != EOF)
        fputc(c, fp2);
    fclose(fp1);
    fclose(fp2);
    return 0;
}
```

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%201.png)

argc의 배열이 3이 아닌 상황 즉, 복사할 파일을 넣지 않은 상황에서는 위와 같이 사용법이 출력 되도록 함

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%202.png)

현재 test2.txt에 아무것도 작성하지 않은 상황

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%203.png)

위와 같이 작성하면 test1.txt의 내용을 test2.txt로 복사한다는 말

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%204.png)

복사가 잘된 모습

## test3.c

```c
#include <stdio.h>
#define MAXLINE 80

/* 텍스트파일에줄번호붙여프린트한다. */
int main(int argc, char *argv[])
{
    FILE *fp;
    int line = 0;
    char buffer[MAXLINE];
    if (argc != 2)
    {
        fprintf(stderr, "사용법:line 파일이름\n");
        return 1;
    }
    if ((fp = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "파일열기오류\n");
        return 2;
    }
    while (fgets(buffer, MAXLINE, fp) != NULL)
    { // 한줄읽기
        line++;
        printf("%3d %s", line, buffer); // 줄번호와함께프린트
    }
    return 0;
}
```

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%205.png)

test2.c 와 같이 실행 파일만 입력했을 경우 argc의 배열이 원하는 만큼 차지 않았기 때문에 사용법을 출력

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%206.png)

## test4.c

```c
#include <stdio.h>
#include "student.h"

/* 학생정보를읽어텍스트파일에저장한다.  */
int main(int argc, char *argv[])
{
    struct student record;
    FILE *fp;
    if (argc != 2)
    {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "w");
    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");
    while (scanf("%d %s %d", &record.id, record.name, &record.score) == 3)
        fprintf(fp, "%d %s %d ", record.id, record.name, record.score);
    fclose(fp);
    return 0;
}
```

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%207.png)

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%208.png)

## test5.c

```c
#include <stdio.h>
#include "student.h"

/* 텍스트파일에서학생정보를읽어프린트한다. */
int main(int argc, char *argv[])
{
    struct student record;
    FILE *fp;
    if (argc != 2)
    {
        fprintf(stderr, "사용법: %s 파일이름\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    printf("%-9s %-7s %-4s\n", "학번", "이름", "점수");
    while (fscanf(fp, "%d %s %d", &record.id, record.name, &record.score) == 3)
        printf("%d %s %d\n", record.id, record.name, record.score);
    fclose(fp);
    return 0;
}
```

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%209.png)

없는 파일을 지정하면 “Segmentation fault”가 출력된다

![Untitled](9%E1%84%8C%E1%85%A1%E1%86%BC%20%E1%84%8B%E1%85%A8%E1%84%8C%E1%85%A6%2054caf32e351c43f3a4325d75ae81cbd2/Untitled%2010.png)