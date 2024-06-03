#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // 프로그램에 디렉토리 이름이 제공되었는지 확인
    if (argc != 2) {
        fprintf(stderr, "사용법: %s <디렉토리 이름>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 입력된 디렉토리 이름 출력
    printf("%s\n", argv[1]);

    return EXIT_SUCCESS;
}