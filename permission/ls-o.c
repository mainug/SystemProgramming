#include <dirent.h> // 디렉토리 처리 함수
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // 파일 상태
#include <unistd.h>
#include <pwd.h> // 사용자 정보

void print_file_info(const char *path) {
    struct stat statbuf; // 파일 상태 정보
    struct passwd *pwd; // 사용자 정보

    if (stat(path, &statbuf) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    pwd = getpwuid(statbuf.st_uid); // 사용자 ID로부터 사용자 정보를 가져옴
    if (!pwd) {
        perror("getpwuid");
        exit(EXIT_FAILURE);
    }

    // 파일 정보 출력
    printf("%10.10s ", pwd->pw_name); // 사용자 이름
    printf("%ld ", (long)statbuf.st_size); // 파일 크기
    printf("%s\n", path); // 파일 이름
}

int main(int argc, char *argv[]) {
    DIR *d;
    struct dirent *dir;
    char *dir_path = argc > 1 ? argv[1] : ".";

    d = opendir(dir_path);
    if (!d) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((dir = readdir(d)) != NULL) {
        // 현재 디렉토리와 상위 디렉토리 표시를 제외
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            continue;

        print_file_info(dir->d_name);
    }

    closedir(d);
    return EXIT_SUCCESS;
}
