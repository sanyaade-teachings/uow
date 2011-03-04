/*
 * TODO
 *	set errno
 *	open() & openat() do not use attributes
 *	most flags in open
 */
#include <windows.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

static HANDLE	ftab[MAX_FD];
static const	mode[]={
		GENERIC_READ+FILE_EXECUTE,
		GENERIC_READ,
		GENERIC_READ+GENERIC_WRITE,
		FILE_LIST_DIRECTORY,
		GENERIC_WRITE
		};

static
valid(f) {
	return f>=0 && f<MAX_FD && ftab[f];
}
		
openat(int f, const char *path, int oflag, ...) {
	static const	share=FILE_SHARE_READ
				+FILE_SHARE_READ
				+FILE_SHARE_DELETE;
	int	i,cf;
	HANDLE	h;
	
	if (valid(f) && close(f)<0)
		return -1;
		
	if (oflag&O_CREAT && oflag&O_EXCL)
		cf=CREATE_NEW;
	else if (oflag&O_CREAT)
		cf=OPEN_ALWAYS;
	else
		cf=OPEN_EXISTING;
	h=CreateFile(path,mode[oflag&7],
		oflag&O_CLOEXEC? 0: share,
		0,cf,0,0);
	if ((int)h<0)
		return -1;
	ftab[f]=h;
	return f;
}

open(const char *path, int oflag, ...) {
	int	i;
	for (i=0; i<MAX_FD && ftab[i]; i++);
	if (i==MAX_FD)
		return -1;
	return openat(i,path,oflag);
}

close(f) {
	if (!valid(f))
		return -1;
	CloseHandle(ftab[f]);
	return 0;
}

write(int f, const void *buf, size_t nbyte) {
	DWORD	ok;
	if (!valid(f))
		return -1;
	WriteFile(ftab[f],buf,nbyte,&ok,0);
	return ok;
}

read(int f, void *buf, size_t nbyte) {
	DWORD	ok;
	if (!valid(f))
		return -1;
	ReadFile(ftab[f],buf,nbyte,&ok,0);
	return ok;
}

chdir(const char *path) {
	return SetCurrentDirectory(path)? 0: -1;
}

char*
getcwd(char *buf, int cap) {
	int	need;
	need=GetCurrentDirectory(0,0);
	if (!buf)
		buf=malloc(cap=need); /* nul accounted for */
	if (cap<need)
		return 0;
	GetCurrentDirectory(cap,buf);
	return buf;
}

mkdir(const char *path) {
	return CreateDirectory(path,0)? 0: -1;
}

rmdir(const char *path) {
	return RemoveDirectory(path)? 0: -1;
}

__initunistd() {
	ftab[0]=GetStdHandle(STD_INPUT_HANDLE);
	ftab[1]=GetStdHandle(STD_OUTPUT_HANDLE);
	ftab[2]=GetStdHandle(STD_ERROR_HANDLE);
}
