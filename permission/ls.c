#include <stdio.h>
#include <dirent.h>

int main() {
    struct dirent *de;  // 포인터로 디렉토리 엔트리를 가리킴
    DIR *dr = opendir("."); // 현재 디렉토리를 연다

    if (dr == NULL) { // 디렉토리를 열 수 없는 경우
        printf("Could not open current directory" );
        return 0;
    }

    while ((de = readdir(dr)) != NULL) {
            printf("%s\n", de->d_name);
    }

    closedir(dr);    
    return 0;
}
