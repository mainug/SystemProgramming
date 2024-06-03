#include <stdio.h>
#include <dirent.h> // 디렉토리 처리 함수

int main() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir("."); // 현재 디렉토리를 엽니다.
    if (!dir) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name); // 파일 또는 디렉토리 이름 출력
    }

    closedir(dir); // 열린 디렉토리를 닫습니다.
    return 0;
}
