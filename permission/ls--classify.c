#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    DIR *d;
    struct dirent *dir;
    struct stat st;

    d = opendir("."); // 현재 디렉토리 열기
    if (!d) {
        perror("opendir");
        return 1;
    }

    while ((dir = readdir(d)) != NULL) {
        if (stat(dir->d_name, &st) == -1) {
            // 파일 상태 정보를 가져오는데 실패
            perror("stat");
            continue;
        }

        // 파일 유형에 따라 출력 형식 결정
        printf("%s", dir->d_name);
        if (S_ISDIR(st.st_mode)) {
            printf("/"); // 디렉토리
        } else if (S_ISLNK(st.st_mode)) {
            printf("@"); // 심볼릭 링크
        } else if (st.st_mode & S_IXUSR) {
            printf("*"); // 사용자 실행 가능 파일
        }
        printf("\n");
    }

    closedir(d); // 디렉토리 스트림 닫기
    return 0;
}