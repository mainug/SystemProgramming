#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

// 파일 정보를 저장할 구조체 정의
struct fileInfo {
    char name[256]; // 파일 이름
    time_t modTime; // 파일 수정 시간
};

// 파일 수정 시간을 비교하는 함수
int compareModTime(const void *a, const void *b) {
    struct fileInfo *fileA = (struct fileInfo *)a;
    struct fileInfo *fileB = (struct fileInfo *)b;
    return (fileB->modTime - fileA->modTime); // 최신 파일이 앞에 오도록 정렬
}

int main() {
    DIR *d;
    struct dirent *dir;
    struct fileInfo *files = NULL; // 파일 정보를 동적 배열로 저장할 포인터
    int count = 0; // 파일 개수

    d = opendir("."); // 현재 디렉토리 열기
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_name[0] == '.') continue; // 숨김 파일은 건너뜀

            struct stat statbuf;
            if (stat(dir->d_name, &statbuf) == -1) continue; // 파일 정보 읽기 실패 시 건너뜀
            
            // 파일 정보를 저장할 메모리 동적 할당 및 초기화
            files = realloc(files, sizeof(struct fileInfo) * (count + 1));
            strcpy(files[count].name, dir->d_name);
            files[count].modTime = statbuf.st_mtime;
            count++;
        }
        closedir(d); // 디렉토리 닫기

        // 파일 수정 시간 기준으로 정렬
        qsort(files, count, sizeof(struct fileInfo), compareModTime);

        // 정렬된 파일 이름 출력
        for (int i = 0; i < count; i++) {
            printf("%s\n", files[i].name);
        }

        free(files); // 동적 할당된 메모리 해제
    } else {
        perror("opendir"); // 디렉토리 열기 실패 시 오류 메시지 출력
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
