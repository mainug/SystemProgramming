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

![Untitled](https://github.com/mainug/SystemProgramming/assets/48702167/54e79771-88d6-4445-9503-70a926120bce)


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

![Untitled 1](https://github.com/mainug/SystemProgramming/assets/48702167/ab6e634b-cab9-43cc-a778-1ddb745d52a2)


argc의 배열이 3이 아닌 상황 즉, 복사할 파일을 넣지 않은 상황에서는 위와 같이 사용법이 출력 되도록 함

![Untitled 2](https://github.com/mainug/SystemProgramming/assets/48702167/237c9b72-f07f-4fb7-b478-d5c8ce0ccc95)


현재 test2.txt에 아무것도 작성하지 않은 상황

![Untitled 3](https://github.com/mainug/SystemProgramming/assets/48702167/cd4ae06c-c93a-4b11-ba43-ace356b4e8f9)


위와 같이 작성하면 test1.txt의 내용을 test2.txt로 복사한다는 말

![Untitled 4](https://github.com/mainug/SystemProgramming/assets/48702167/afacaec7-accf-4ed5-b40e-720d19026162)


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

![Untitled 5](https://github.com/mainug/SystemProgramming/assets/48702167/a2d37040-7e56-41ee-9314-cb34c51ccc18)


test2.c 와 같이 실행 파일만 입력했을 경우 argc의 배열이 원하는 만큼 차지 않았기 때문에 사용법을 출력

![Untitled 6](https://github.com/mainug/SystemProgramming/assets/48702167/d7152236-3078-4015-9579-98b031fe8b63)


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

![Untitled 7](https://github.com/mainug/SystemProgramming/assets/48702167/808cee98-fb51-44a0-8628-57dfa6bfe35b)


![Untitled 8](https://github.com/mainug/SystemProgramming/assets/48702167/dcc189d1-63c8-4167-b280-3f5ccf59e591)


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

![Untitled 9](https://github.com/mainug/SystemProgramming/assets/48702167/da427661-a9a0-4b5a-968c-f821cd8a98c2)


없는 파일을 지정하면 “Segmentation fault”가 출력된다

![Untitled 10](https://github.com/mainug/SystemProgramming/assets/48702167/9b1a0b7e-e57f-47dc-ab9a-755a73092d1d)
