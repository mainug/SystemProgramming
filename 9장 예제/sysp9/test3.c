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
