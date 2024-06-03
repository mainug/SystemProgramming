#include <stdio.h>
#include <dirent.h> // 디렉토리 처리 함수
#include <string.h> // 문자열 처리 함수

int main() {
    DIR *d;
    struct dirent *dir;
    d = opendir("."); // 현재 디렉토리 열기
    if (!d) {
        perror("opendir");
        return 1;
    }

    while ((dir = readdir(d)) != NULL) {
        size_t len = strlen(dir->d_name);
        // 파일 이름이 최소 1글자 이상이고 마지막 문자가 '~'인 경우 스킵
        if (len > 0 && dir->d_name[len - 1] == '~') {
            continue;
        }
        printf("%s\n", dir->d_name);
    }

    closedir(d); // 디렉토리 스트림 닫기
    return 0;
}