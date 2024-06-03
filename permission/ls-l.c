#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void printPermissions(mode_t mode) {
    // 파일 권한 출력
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *d;
    struct dirent *dir;
    struct stat fileInfo;
    char timeBuf[80];
    struct tm lt;
    
    d = opendir("."); // 현재 디렉토리 열기
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            stat(dir->d_name, &fileInfo); // 파일 정보 가져오기
            
            printPermissions(fileInfo.st_mode); // 파일 권한 출력
            
            printf(" %ld", fileInfo.st_nlink); // 링크 수 출력
            
            // 소유자 이름과 그룹 이름 출력
            printf(" %s %s", getpwuid(fileInfo.st_uid)->pw_name, getgrgid(fileInfo.st_gid)->gr_name);
            
            printf(" %5ld", fileInfo.st_size); // 파일 크기 출력
            
            // 마지막 수정 시간 출력
            localtime_r(&fileInfo.st_mtime, &lt);
            strftime(timeBuf, sizeof(timeBuf), "%b %d %H:%M", &lt);
            printf(" %s", timeBuf);
            
            printf(" %s\n", dir->d_name); // 파일 이름 출력
        }
        closedir(d); // 디렉토리 닫기
    }
    return 0;
}