#include <unistd.h>
#include <sys/dirent.h>
main() {
	DIR		*dir;
	struct dirent	*ent;
	dir=opendir(".");
	while (ent=readdir(dir))
		puts(ent->d_name);
	closedir(dir);
}
