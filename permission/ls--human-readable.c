#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void print_human_readable_size(double size) {
    // 파일 크기 단위 배열
    const char *units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB"};
    int i = 0;

    // 파일 크기를 1024로 나누어 적절한 단위로 변환
    while (size >= 1024) {
        size /= 1024;
        i++;
    }

    // 변환된 파일 크기와 단위를 출력
    printf("%.*f%s", i, size, units[i]);
}

int main() {
    DIR *d;
    struct dirent *dir;
    struct stat st;
    char *path = "."; // 현재 디렉토리를 가리킴

    // 현재 디렉토리 열기
    d = opendir(path);
    if (d) {
        // 디렉토리의 각 파일에 대해 반복
        while ((dir = readdir(d)) != NULL) {
            // 파일의 전체 경로 생성
            char filePath[1024];
            sprintf(filePath, "%s/%s", path, dir->d_name);

            // 파일의 상태 정보 가져오기
            if (stat(filePath, &st) == 0) {
                // 파일 이름 출력
                printf("%s: ", dir->d_name);

                // 파일 크기를 사람이 읽기 쉬운 형태로 출력
                print_human_readable_size((double)st.st_size);
                printf("\n");
            }
        }
        // 디렉토리 닫기
        closedir(d);
    }

    return 0;
}