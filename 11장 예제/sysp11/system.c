#include <sys/types.h> /* system.c*/
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int mysystem(const char *cmdstring)
{
    pid_t pid;
    int status;
    if (cmdstring == NULL) /* 명령어가NULL인경우*/
        return (1);
    if ((pid = fork()) < 0)
    {
        status = -1; /* 프로세스생성실패*/
    }
    else if (pid == 0)
    { /* 자식프로세스*/
        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127); /* execl오류*/
    }
    else
    { /* 부모프로세스*/
        while (waitpid(pid, &status, 0) < 0)
            if (errno != EINTR)
            {
                status = -1; /* waitpid()로부터EINTR외의오류*/
                break;
            }
    }
    return (status);
}
