#ifndef UNISTD_H
#define UNISTD_H

#include <stddef.h>

#define MAX_FD	128

extern
	open(const char *path, int oflag, ...),
	openat(int fd, const char *path, int oflag, ...),
	close(int fd),
	write(int f, const void *buf, size_t nbyte),
	read(int f, const void *buf, size_t nbyte),
	chdir(const char *path),
	mkdir(const char *path);
	rmdir(const char *path);

#endif
