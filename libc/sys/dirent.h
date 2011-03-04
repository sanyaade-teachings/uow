#ifndef DIRENT_H
#define DIRENT_H

#include <sys/types.h>
#include <stddef.h>

typedef struct _DIR DIR;

struct dirent {
	char	d_name[NAME_MAX+1];
	ino_t	d_ino;
};

extern DIR
	*opendir(const char *path);
extern
	closedir(DIR *dir);
extern struct dirent
	*readdir(DIR *dir);




#endif
