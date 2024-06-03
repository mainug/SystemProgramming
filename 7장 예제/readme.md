# 7장 예제

## ftype.c

### 코드

```c
#include <sys/types.h> 
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/* 파일 타입을 검사한다. */
int main(int argc, char *argv[])
{ 
	int i;
	struct stat buf;
	for (i = 1; i < argc; i++) {
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0) {
			perror("lstat()"); 
			continue;
		}
		if (S_ISREG(buf.st_mode)) 
			printf("%s \n", "일반 파일");
		if (S_ISDIR(buf.st_mode)) 
			printf("%s \n", "디렉터리");
		if (S_ISCHR(buf.st_mode)) 
			printf("%s \n", "문자 장치 파일");
		if (S_ISBLK(buf.st_mode)) 
			printf("%s \n", "블록 장치 파일");
		if (S_ISFIFO(buf.st_mode)) 
			printf("%s \n", "FIFO 파일");
		if (S_ISLNK(buf.st_mode)) 
			printf("%s \n", "심볼릭 링크");
		if (S_ISSOCK(buf.st_mode)) 
			printf("%s \n", "소켓");
		}
	exit(0);
}
```

### 결과

![Untitled](https://github.com/mainug/SystemProgramming/assets/48702167/62918e25-469b-4088-b04c-b0b70bece099)


위 코드의 실행 파일을 실행할 때 어떤 파일인지 알고 싶은 파일(예시에서는 ftype.c 파일을 그대로 사용)을 공백 뒤에 넣어 확인

## fchmod.c

### 코드

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
/* 파일 사용권한을 변경한다. */
int main(int argc, char *argv[]) {
	long strtol( );
	int newmode;
	newmode = (int) strtol(argv[1], (char **) NULL, 8);
	if (chmod(argv[2], newmode) == -1) {
		perror(argv[2]);
		exit(1);
	}
	exit(0);
}
```

### 결과

![Untitled 1](https://github.com/mainug/SystemProgramming/assets/48702167/07a7d6ed-e98e-4b53-a718-14df7b5b11d8)


현재 fchmod.c 파일의 권한은 rw-r—r—

권한은 소유자(읽기/쓰기)권한, 그룹(읽기)권한, 다른 사용자(읽기)권한이 주어져 있다.

![Untitled 2](https://github.com/mainug/SystemProgramming/assets/48702167/18d8f68b-be74-4f61-80bc-70eb4e146123)


fchmod.c 코드를 실행하여 10진수를 2진수로 변환해 권한을 부여하고 원하는 파일을 뒤에 삽입

![Untitled 3](https://github.com/mainug/SystemProgramming/assets/48702167/dc987331-1af9-4691-92c6-0fcb3d1b6481)


현재 fchmod.c의 권한이 변경된 것을 확인 가능

## cptime.c

### 코드

```c
#include <sys/types.h> #include <sys/stat.h> 
#include <sys/time.h> #include <utime.h> 
#include <stdio.h> #include <stdlib.h>
int main(int argc, char *argv[]) 
{
	struct stat buf; // 파일 상태 저장을 위한 변수
	struct utimbuf time;
	if (argc < 3) {
		fprintf(stderr, "사용법: cptime file1 file2\n");
		exit(1);
	}
	if (stat(argv[1], &buf) <0) { // 상태 가져오기
		perror("stat()");
		exit(-1);
	}
	time.actime = buf.st_atime;
	time.modtime = buf.st_mtime;
	if (utime(argv[2], &time)) // 접근, 수정 시간 복사
		perror("utime");
	else exit(0);
}
```

### 결과

![Untitled 4](https://github.com/mainug/SystemProgramming/assets/48702167/e3386d13-695b-4960-881c-d0ad3fb6c365)


현재 cptime.c의 시간 정보는 Apr 30 18:44. 이 시간 정보를 복사해 ftype.c에 적용하려고 한다.

![Untitled 5](https://github.com/mainug/SystemProgramming/assets/48702167/86c34cd0-b193-481c-a218-62e5fd33ab9c)


시간 정보를 복사할 파일을 앞에 넣고 복사한 정보를 적용할 파일을 뒤에 넣는다.

![Untitled 6](https://github.com/mainug/SystemProgramming/assets/48702167/95e37b3a-cc3e-4f0e-ab51-f0f7f6ed8bce)


ftype.c의 시간 정보가 cptime.와 같아진 모습

## list1.c

### 코드

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

/* 디렉터리 내의 파일 이름들을 리스트한다. */
int main(int argc, char **argv)
{
	DIR *dp;
	char *dir;
	struct dirent *d;
	struct stat st;
	char path[BUFSIZ+1];
	
	if (argc == 1)
		dir = "."; // 현재 디렉터리를 대상으로
	else dir = argv[1];

	if ((dp = opendir(dir)) == NULL) // 디렉터리 열기
		perror(dir);
		
	while ((d = readdir(dp)) != NULL) // 각 디렉터리 엔트리에 대해
		printf("%s \n", d->d_name); // 파일 이름 프린트

	closedir(dp);
	exit(0);
}
```

### 결과

위 코드는 사용자가 원하는 곳의 디렉터리를 지정해 리스트를 보여주는 코드

![Untitled 7](https://github.com/mainug/SystemProgramming/assets/48702167/f3c213a7-3b11-4c38-8a51-0a0eca6f6614)


![Untitled 8](https://github.com/mainug/SystemProgramming/assets/48702167/a8186f80-c26c-44f0-95d6-6ea82e9e4b0e)


코드를 실행하면 현재 디렉터리에 있는 파일들을 리스트로 만들어 출력해준다.

## list2.c

### 코드

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*);

/* 디렉터리 내용을 자세히 리스트한다. */
int main(int argc, char **argv)
{
	DIR *dp;
	char *dir;
	struct stat st;
	struct dirent *d;
	char path[BUFSIZ+1];
	if (argc == 1)
		dir = ".";
	else dir = argv[1];

	if ((dp = opendir(dir)) == NULL) // 디렉터리 열기
		perror(dir);

	while ((d = readdir(dp)) != NULL) { // 디렉터리의 각 파일에 대해
		sprintf(path, "%s/%s", dir, d->d_name); // 파일경로명 만들기
		if (lstat(path, &st) < 0) // 파일 상태 정보 가져오기
			perror(path);
			printStat(path, d->d_name, &st); // 상태 정보 출력
			putchar('\n');
	}

	closedir(dp);
	exit(0);
}

/* 파일 상태 정보를 출력 */
void printStat(char *pathname, char *file, struct stat *st) {

	printf("%5d ", st->st_blocks);
	printf("%c%s ", type(st->st_mode), perm(st->st_mode));
	printf("%3d ", st->st_nlink);
	printf("%s %s ", getpwuid(st->st_uid)->pw_name,
		getgrgid(st->st_gid)->gr_name);
	printf("%9d ", st->st_size);
	printf("%.12s ", ctime(&st->st_mtime)+4);
	printf("%s", file);
}
 /* 파일 타입을 리턴 */
char type(mode_t mode) {

	if (S_ISREG(mode))
		return('-');
	if (S_ISDIR(mode))
		return('d');
	if (S_ISCHR(mode))
		return('c');
	if (S_ISBLK(mode))
		return('b');
	if (S_ISLNK(mode))
		return('l');
	if (S_ISFIFO(mode))
		return('p');
	if (S_ISSOCK(mode))
		return('s');
}
/* 파일 사용권한을 리턴 */
char* perm(mode_t mode) {
	int i;
	static char perms[10] = "---------";

	for (i=0; i < 3; i++) {
		if (mode & (S_IREAD >> i*3))
			perms[i*3] = 'r';
		if (mode & (S_IWRITE >> i*3))
			perms[i*3+1] = 'w';
		if (mode & (S_IEXEC >> i*3))
			perms[i*3+2] = 'x';
	}
	return(perms);
}
```
