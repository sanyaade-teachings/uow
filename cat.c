#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

dump(f) {
	char	buf[4096];
	int	n;
	while (n=read(f,buf,4096))
		write(1,buf,n);
}

main(int argc, char **argv) {
	int	f,nf=0;
	while (*++argv) {
		if (++nf && (f=open(*argv,O_RDONLY))) {
			dump(f);
			close(f);
		} else {
			fprintf(stderr,
				"cat: %s does not exist\n",
				*argv);
			exit(1);
		}
	}
	if (!nf)
		dump(1);
	return 0;
}
