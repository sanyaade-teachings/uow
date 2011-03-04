#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <vec.h>

static char*
quote(char *arg, char *s) {
	int	delim=*s++;
	while (*s && *s!=delim)
		catvec(arg,*s++);
	return s+(*s==delim);
}

static char**
setargv(int *argc) {
	char	**argv,*a,*c;
	
	c=GetCommandLine();
	argv=newvec();
	
	while (*c) {
		if (isspace(*c)) {
			c++;
			continue;
		}
		
		a=newvec();
		if (*c=='"' || *c=='\'')
			c=quote(a,c);
		else
			while (*c && !isspace(*c))
				if (*c=='"' || *c=='\'')
					c=quote(a,c);
				else
					catvec(a,*c++);
		catvec(argv,catvec(a,0));
	}
	argc && (*argc=lenvec(argv));
	return catvec(argv,0);
}

mainCRTStartup() {
	char	**argv;
	int	argc;
	__initctype();
	__initunistd();
	__initstdlib();
	__initstdin();
	argv=setargv(&argc);
	exit(main(argc,argv));
}
