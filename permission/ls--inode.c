#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void print_human_readable_size(double size) {
    // 파일 크기를 보기 좋게 출력하는 함수
    const char *units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB"};
    int i = 0;
    while (size >= 1024) {
        size /= 1024;
        i++;
    }
    printf("%.*f%s", i, size, units[i]);
}

void print_last_status_change_time(time_t t) {
    // 파일의 마지막 상태 변경 시간을 출력하는 함수
    char buffer[80];
    struct tm *timeinfo;
    timeinfo = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("%s", buffer);
}

int main(int argc, char *argv[]) {
    DIR *d;
    struct dirent *dir;
    struct stat st;
    char *path = ".";
    int show_ctime = 0;
    int show_inode = 0; // inode 번호를 출력할지 여부를 결정하는 변수 추가

    // 명령줄 인수를 확인하여 -c 또는 -i 옵션이 있는지 확인
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            show_ctime = 1;
        } else if (strcmp(argv[i], "-i") == 0) {
            show_inode = 1; // -i 옵션 발견 시 show_inode를 1로 설정
        } else {
            path = argv[i];
        }
    }

    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            char filePath[1024];
            sprintf(filePath, "%s/%s", path, dir->d_name);

            if (stat(filePath, &st) == 0) {
                // -i 옵션이 지정되면 inode 번호를 출력
                if (show_inode) {
                    printf("%lu ", (unsigned long)st.st_ino); // inode 번호 출력
                }
                // 파일 이름 출력
                printf("%s: ", dir->d_name);

                // 파일 크기를 인간이 읽기 쉬운 형식으로 출력
                print_human_readable_size((double)st.st_size);
                printf(" ");

                // -c 옵션이 있는 경우, 마지막 상태 변경 시간을 출력
                if (show_ctime) {
                    print_last_status_change_time(st.st_ctime);
                }
                printf("\n");
            }
        }
        closedir(d);
    } else {
        perror("opendir");
        return EXIT_FAILURE;
    }

    return 0;
}