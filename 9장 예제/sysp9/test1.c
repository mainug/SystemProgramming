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
