#include <stdio.h>
#include <dirent.h> // 디렉토리 관련 함수를 위한 헤더 파일
#include <sys/stat.h> // 파일 정보를 가져오기 위한 헤더 파일

// 파일 목록과 크기를 출력하는 함수
void listFiles(const char *path, int showSizeInKB) {
    struct dirent *entry; // 디렉토리 내의 항목에 대한 정보를 저장
    struct stat fileInfo; // 파일의 상세 정보를 저장
    DIR *dir = opendir(path); // 디렉토리 열기

    if (dir == NULL) {
        printf("Unable to open directory.\n");
        return;
    }

    while ((entry = readdir(dir)) != NULL) { // 디렉토리 내의 모든 파일을 순회
        stat(entry->d_name, &fileInfo); // 파일 정보를 가져옴
        
        // 파일 크기를 킬로바이트 단위로 출력할지 결정
        if (showSizeInKB) {
            printf("%-20s %10ld KB\n", entry->d_name, fileInfo.st_size / 1024);
        } else {
            printf("%-20s %10ld bytes\n", entry->d_name, fileInfo.st_size);
        }
    }

    closedir(dir); // 디렉토리 닫기
}

int main(int argc, char *argv[]) {
    int showSizeInKB = 0; // 킬로바이트 단위로 출력할지 여부를 저장하는 변수

    // 명령줄 인수 처리
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && argv[i][1] == 'k') {
            showSizeInKB = 1; // '-k' 옵션이 주어지면 showSizeInKB를 1로 설정
        }
    }

    listFiles(".", showSizeInKB); // 현재 디렉토리의 파일 목록과 크기 출력
    return 0;
}