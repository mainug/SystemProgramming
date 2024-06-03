#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

// 파일 크기를 인간이 읽기 쉬운 형식으로 출력하는 함수
void print_human_readable_size(double size) {
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

// 마지막 상태 변경 시간을 출력하는 함수
void print_last_status_change_time(time_t t) {
    char buffer[80];
    struct tm *timeinfo;

    // time_t 형식을 struct tm 형식으로 변환
    timeinfo = localtime(&t);

    // struct tm 형식을 인간이 읽을 수 있는 문자열로 변환
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

    // 변환된 시간 문자열을 출력
    printf("%s", buffer);
}

int main(int argc, char *argv[]) {
    DIR *d;
    struct dirent *dir;
    struct stat st;
    char *path = ".";
    int show_ctime = 0;

    // 명령줄 인수를 확인하여 -c 옵션이 있는지 확인
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            show_ctime = 1;
        } else {
            path = argv[i];
        }
    }

    // 지정된 디렉토리를 엽니다
    d = opendir(path);
    if (d) {
        // 디렉토리 내의 각 파일을 반복하여 처리
        while ((dir = readdir(d)) != NULL) {
            char filePath[1024];
            sprintf(filePath, "%s/%s", path, dir->d_name);

            // 파일의 상태 정보를 얻습니다
            if (stat(filePath, &st) == 0) {
                // 파일 이름을 출력
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
        // 디렉토리를 닫습니다
        closedir(d);
    } else {
        perror("opendir");
        return EXIT_FAILURE;
    }

    return 0;
}
