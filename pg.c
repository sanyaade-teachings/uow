#include <stdio.h>
#include "libterm.h"

char	buf[1024];
int	rows=24;

copy(FILE *f, int n) {
	while (n-->0)
		if (!fgets(buf,sizeof buf,f))
			exit(0);
		else
			fputs(buf,stdout);
	return 1;
}

all(FILE *f) {
	int	c;
	copy(f,rows);
	while(c=tgetsc())
		if (c=='j' || c=='\r' || c=='\n')
			copy(f,1);
		else if (c==' ')
			copy(f,rows);
		else if (c=='q' || c=='Q')
			break;
}

main(int argc, char **argv) {
	FILE	*f;
	if (argc>1)
		while (*++argv)
			if (**argv=='-')
				if (!strcmp(*argv,"-"))
					all(f);
				else if (isdigit(argv[0][2]))
					rows=atoi(argv[0]+1);
				else;
			else if (f=fopen(*argv,"rb"))
				all(f);
			else
				printf("cannot open %d\n",*argv);
	else
		all(stdin);
	return 0;
}
