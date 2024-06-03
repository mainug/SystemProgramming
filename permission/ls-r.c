#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// 파일 이름 비교 함수 (역순)
int compare(const void *a, const void *b) {
    return strcmp(*(char**)b, *(char**)a);
}

int main() {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    char *files[256]; // 파일 이름 저장을 위한 배열
    int count = 0;

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_name[0] == '.') continue; // 숨김 파일은 제외
            files[count] = malloc(strlen(dir->d_name) + 1);
            strcpy(files[count], dir->d_name);
            count++;
        }
        closedir(d);

        // 파일 이름을 역순으로 정렬
        qsort(files, count, sizeof(char *), compare);

        // 정렬된 파일 이름 출력
        for (int i = 0; i < count; i++) {
            printf("%s\n", files[i]);
            free(files[i]); // 동적 할당된 메모리 해제
        }
    }

    return 0;
}
