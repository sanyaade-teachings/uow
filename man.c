#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*pager,*manpath;

char*
openpaths(char *final, char *paths, char fn[256]) {
	char	tmp[1024];
	char	*mark,*p;
	FILE	*f;
	
	mark=paths;
	p=paths;
	while (*p) {
		if (*p==':') {
			mark=++p;
			continue;
		}
		while (*p && *p!=':' && *p!=';')
			p++;
		strncpy(tmp,mark,p-mark);
		tmp[(p-mark)]='/';
		strcpy(tmp+(p-mark)+1, fn);
		if (f=fopen(tmp,"rb")) {
			fclose(f);
			return strcpy(final,tmp);
		}
		mark=p+1;
	}
	*final=0;
	return 0;
}

char*
manopen(char *final, char *paths, int start, int end, char fn[256]) {
	char	*ret,tmp[256];
	int	sect;
	for (sect=start; sect<=end; sect++) {
		sprintf(tmp,"man%d/%s.%d",sect,fn,sect);
		if (ret=openpaths(final,paths,tmp))
			return ret;
	}
	return 0;
}

run(char *fn) {
	char cmd[1024];
	sprintf(cmd,"nroff -man %s | %s",fn,pager);
	system(cmd);
}

main(int argc, char **argv) {
	char	fn[256];
	int	n=1,m=9;
	
	if (!(manpath=getenv("MANPATH")))
		manpath="../usr/man:.";
	if (!(pager=getenv("PAGER")))
		pager="pg";
	while (*++argv)
		if (isdigit(**argv))
			n=m=atoi(*argv);
		else if (strchr(*argv,'/') || strchr(*argv,'\\'))
			run(*argv);
		else if (manopen(fn,manpath,n,m,*argv))
			run(fn);
		else
			printf("man: No manual entry for %s\n", *argv);
}
