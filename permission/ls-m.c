#include <stdio.h>
#include <dirent.h> // 디렉토리 관련 함수들을 사용하기 위한 헤더 파일

void listFilesWithComma(const char *path) {
    struct dirent *entry; // 디렉토리 항목 정보를 저장할 구조체
    DIR *dir = opendir(path); // 주어진 경로의 디렉토리를 열기
    int isFirst = 1; // 첫 번째 항목인지 판별하기 위한 변수. 첫 항목이면 1, 그렇지 않으면 0

    if (dir == NULL) { // 디렉토리를 열 수 없는 경우
        printf("Cannot open directory.\n");
        return; // 함수를 종료하고 에러 메시지 출력
    }

    while ((entry = readdir(dir)) != NULL) { // 디렉토리 내의 모든 항목을 순회
        // 숨겨진 파일(이름이 '.'으로 시작하는 파일)은 제외
        if (entry->d_name[0] != '.') {
            if (!isFirst) { // 첫 번째 항목이 아니라면
                printf(", "); // 항목 사이에 쉼표와 공백을 출력
            } else {
                isFirst = 0; // 첫 번째 항목을 처리했으므로 이후부터는 0으로 설정
            }
            printf("%s", entry->d_name); // 파일 또는 디렉토리 이름 출력
        }
    }
    printf("\n"); // 모든 항목을 출력한 후 줄바꿈

    closedir(dir); // 열린 디렉토리 스트림을 닫음
}

int main() {
    listFilesWithComma("."); // 현재 디렉토리('.')를 인자로 함수 호출
    return 0; // 프로그램 정상 종료
}
