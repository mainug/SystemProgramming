#include <stdio.h>
#include <dirent.h>
#include <ctype.h> // isprint 함수를 위한 헤더 파일

void print_escaped_filename(const char *filename) {
    while (*filename) {
        unsigned char c = *filename++;
        // 인쇄 가능한 문자인 경우 그대로 출력
        if (isprint(c)) {
            putchar(c);
        } else {
            // 비인쇄 가능한 문자는 8진수 코드로 출력
            printf("\\%03o", c);
        }
    }
    printf("\n");
}

int main() {
    DIR *d;
    struct dirent *dir;
    d = opendir("."); // 현재 디렉토리 열기
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            print_escaped_filename(dir->d_name);
        }
        closedir(d);
    }
    return 0;
}
