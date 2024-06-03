#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR *d;
    struct dirent *dir;
    char *path = "."; // 현재 디렉토리를 기본 경로로 설정

    // 커맨드 라인에서 경로가 제공되면 해당 경로 사용
    if (argc > 1) path = argv[1];

    // 디렉토리 열기
    d = opendir(path);

    if (d) {
        while ((dir = readdir(d)) != NULL) {
            printf("%s\n", dir->d_name); // 파일/디렉토리 이름 출력
        }
        closedir(d); // 디렉토리 닫기
    } else {
        // 디렉토리 열기 실패 시 메시지 출력
        perror("opendir");
        return 1;
    }

    return 0;
}
