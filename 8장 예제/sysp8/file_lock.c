#include <stdio.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    static struct flock lock;
    int fd, ret, c;
    if (argc < 2)
    {
        fprintf(stderr, "사용법: %s 파일\n", argv[0]);
        exit(1);
    }
    fd = open(argv[1], O_WRONLY);
    if (fd == -1)
    {
        printf("파일열기실패\n");
        exit(1);
    }
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();
    ret = fcntl(fd, F_SETLKW, &lock);
    if (ret == 0)
    { // 파일잠금성공하면
        c = getchar();
    }
}
