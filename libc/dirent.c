#include <sys/dirent.h>
#include <stdlib.h>
#include <vec.h>
#include <windows.h>

struct _DIR {
	HANDLE		handle;
	WIN32_FIND_DATA	dat;
	struct dirent	ent;
	int		first;
	char		*spec;
};

DIR*
opendir(const char *path) {
	DIR		*dir=malloc(sizeof *dir);
	const char	*s;
	
	dir->spec=newvec();
	for (s=path; *s; s++)
		catvec(dir->spec,*s);
	catvec(dir->spec,'/');
	catvec(dir->spec,'*');
	catvec(dir->spec,0);
	
	dir->handle=FindFirstFile(dir->spec, &dir->dat);
	dir->first=1;
	if (dir->handle!=INVALID_HANDLE_VALUE)
		return dir;
	free(dir);
	return 0;
}

closedir(DIR *dir) {
	FindClose(dir->handle);
	free(dir->spec);
	free(dir);
}

struct dirent*
readdir(DIR *dir) {
	if (!dir->first)
		if (!FindNextFile(dir->handle, &dir->dat))
			return 0;
		else;
	else
		dir->first=0;
	strcpy(dir->ent.d_name, dir->dat.cFileName);
	dir->ent.d_ino=0;
	return &dir->ent;
}
