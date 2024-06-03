#include <stdio.h>
#include <dirent.h> // 디렉토리 처리 함수

int main() {
    DIR *d;
    struct dirent *dir;
    d = opendir("."); // 현재 디렉토리 열기
    if (!d) {
        perror("opendir");
        return 1;
    }

    while ((dir = readdir(d)) != NULL) {
        // 현재 디렉토리(.)와 상위 디렉토리(..)를 제외한 항목만 출력
        if (dir->d_name[0] == '.' && (dir->d_name[1] == '\0' || (dir->d_name[1] == '.' && dir->d_name[2] == '\0'))) {
            continue; // 현재 디렉토리와 상위 디렉토리의 경우 스킵
        }
        printf("%s\n", dir->d_name);
    }

    closedir(d); // 디렉토리 스트림 닫기
    return 0;
}
