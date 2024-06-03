#include <dirent.h> // 디렉토리 관련 함수를 사용하기 위한 헤더 파일
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // 파일 상태 정보를 얻기 위한 헤더 파일
#include <unistd.h>

void print_file_info(const char *path) {
    struct stat statbuf; // 파일의 상태 정보를 저장하기 위한 구조체

    // stat 함수를 사용하여 파일의 상태 정보를 가져옴. 실패 시 오류 메시지 출력 후 종료
    if (stat(path, &statbuf) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // 파일 정보 출력
    printf("%ld\t", (long)statbuf.st_ino); // inode 번호
    printf("%o\t", (unsigned int)statbuf.st_mode); // 파일 모드 (권한)
    printf("%ld\t", (long)statbuf.st_nlink); // 하드 링크의 수
    printf("%ld\t", (long)statbuf.st_uid); // 사용자 ID
    printf("%ld\t", (long)statbuf.st_gid); // 그룹 ID
    printf("%ld\t", (long)statbuf.st_size); // 파일 크기 (바이트 단위)
    printf("%s\n", path); // 파일 이름
}

int main(int argc, char *argv[]) {
    DIR *d; // 디렉토리 스트림을 위한 포인터
    struct dirent *dir; // 디렉토리 내의 항목에 대한 정보를 저장하기 위한 구조체
    char *dir_path = argc > 1 ? argv[1] : "."; // 사용자가 디렉토리 경로를 입력하지 않은 경우 현재 디렉토리로 설정

    // opendir 함수를 사용하여 디렉토리를 열고, 실패 시 오류 메시지 출력 후 종료
    d = opendir(dir_path);
    if (d == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // 디렉토리 내의 모든 파일/디렉토리에 대하여 정보를 출력
    while ((dir = readdir(d)) != NULL) {
        print_file_info(dir->d_name); // 파일/디렉토리 이름을 인자로 하여 정보 출력 함수 호출
    }

    closedir(d); // 열린 디렉토리 스트림을 닫음
    return EXIT_SUCCESS;
}
