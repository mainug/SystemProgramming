#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void printPermissions(mode_t mode)
{
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

int main(int argc, char *argv[])
{
    DIR *d;
    struct dirent *dir;
    struct stat statbuf;
    char timebuf[80];
    struct passwd *pwd;
    struct group *grp;

    d = opendir("."); // 현재 디렉토리 열기
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // -a 옵션 처리: 숨김 파일을 포함하여 모든 파일 출력
            // 기본적으로 readdir은 모든 파일을 반환하므로, 여기서는 추가적인 조건 없이 모든 파일을 처리합니다.

            if (stat(dir->d_name, &statbuf) == -1)
            {
                continue; // 파일 정보를 가져오는 데 실패한 경우, 다음 파일로 넘어갑니다.
            }

            printPermissions(statbuf.st_mode); // 파일 권한 출력
            printf(" %lu", statbuf.st_nlink);  // 링크 수

            if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
                printf(" %s", pwd->pw_name); // 소유자 이름
            else
                printf(" %d", statbuf.st_uid);

            if ((grp = getgrgid(statbuf.st_gid)) != NULL)
                printf(" %s", grp->gr_name); // 그룹 이름
            else
                printf(" %d", statbuf.st_gid);

            printf(" %5ld", statbuf.st_size); // 파일 크기

            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&statbuf.st_mtime));
            printf(" %s", timebuf); // 마지막 수정 시간

            printf(" %s\n", dir->d_name); // 파일 이름
        }
        closedir(d); // 디렉토리 닫기
    }
    return 0;
}
