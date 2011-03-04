#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdarg.h>

static FILE	tab[MAX_FILE];

__initstdin() {
	int i;
	for (i=0; i<MAX_FILE; i++)
		tab[i].fd=-1;
	stdin=fdopen(0,"rb");
	stdout=fdopen(1,"wb");
	stderr=fdopen(2,"wb");
}

static
parsemode(const char *mode) {
	if (!strcmp("r",mode))		return O_RDONLY;
	if (!strcmp("r+",mode))		return O_RDWR;
	if (!strcmp("rb",mode))		return O_RDONLY;
	if (!strcmp("r+b",mode))	return O_RDWR;
	if (!strcmp("rb+",mode))	return O_RDWR;
	
	if (!strcmp("w",mode))		return O_WRONLY+O_CREAT;
	if (!strcmp("w+",mode))		return O_RDWR+O_CREAT;
	if (!strcmp("wb",mode))		return O_WRONLY+O_CREAT;
	if (!strcmp("w+b",mode))	return O_RDWR+O_CREAT;
	if (!strcmp("wb+",mode))	return O_RDWR+O_CREAT;
	return -1;
}

FILE*
fdopen(int fd, const char *mode) {
	FILE	*f;
	for (f=tab; f<tab+MAX_FILE && f->fd>=0; f++);
	if (f==tab+MAX_FILE)
		return 0;
	f->mod=parsemode(mode);
	if (f->mod<0)
		return 0;
	f->fd=fd;
	f->eof=0;
	f->err=0;
	return f;
}

FILE*
fopen(const char *name, const char *mode) {
	int	fd,oflag;
	FILE	*f;
	oflag=parsemode(mode);
	if (oflag<0)
		return 0;
	fd=open(name,oflag);
	if (fd<0)
		return 0;
	if (f=fdopen(fd,mode))
		return f;
	close(fd);
	return 0;
}

fclose(FILE *f) {
	if (close(f->fd)<0)
		return -1;
	f->fd=0;
	return 0;
}

_fcloseall() {
	FILE *f;
	int	n=0;
	for (f=tab+3; f<tab+MAX_FILE; f++)
		if (f->fd) {
			n++;
			fclose(f);
		}
	return n;
}

fflush(FILE *f) {
	return 0;
}

// long
//fgetpos(FILE *f) {
//	return tell(f);
//}
//
// long
//ftell(FILE *f) {
//	return tell(f);
//}

void
clearerr(FILE *f) {
	f->err=0;
}

feof(FILE *f) {
	return f->eof;
}

ferror(FILE *f) {
	return f->err;
}

fgetc(FILE *f) {
	char	buf;
	int	c=read(f->fd,&buf,1)==1? (buf&255): (f->eof=-1);
//	ONLY IN TEXT MODE
	return c=='\r'? fgetc(f): c;
}

fputc(int c, FILE* f) {
	char	buf=c;
//	ONLY IN TEXT MODE
	if (c=='\r')
		return c;
	return write(f->fd,&buf,1)==1? c: -1;
}

fread(void *buf, int sz, int n, FILE *f) {
	int	ok=0,c;
	while (ok<n && (c=fgetc(f))>=0)
		((char*)buf)[ok++]=c;
	return ok<0? -1: (sz? ok/sz: 0);
}

fwrite(void *buf, int sz, int n, FILE *f) {
	int	ok=0;
	while (ok<n && fputc(((char*)buf)[ok++],f)>=0);
	return sz? ok/sz: 0;
}

fputs(const char *s, FILE *f) {
	int	ok;
	while (*s && (ok=putc(*s++,f)>=0));
	return ok;
}

puts(const char *s) {
	fputs(s,stdout);
	return putc('\n',stdout);
}

char*
fgets(char *buf, size_t max, FILE *f) {
	int	c;
	size_t	n=0;
	while (n<max-1 && (c=getc(f))>=0) {
		buf[n++]=c;
		if (c=='\n')
			break;
	}
	if (!n)
		return 0;
	buf[n]=0;
	return buf;
}

char*
gets(char *buf) {
	int	c,n=0;
	while ((c=getchar())>=0 && c!='\n')
		buf[n++]=c;
	buf[n]=0;
	return buf;
}

static
itoa(unsigned x, int base, FILE *f) {
	if (base==10 && (int)x<0) {
		putc('-',f);
		itoa(-(int)x,base,f);
	} else {
		if (x/base)
			itoa(x/base,base,f);
		putc("0123456789abcdef"[x%base],f);
	}
}

vfprintf(FILE *f, char *fmt, va_list ap) {
	char	*s;
	int	n;
	for ( ; *fmt; fmt++)
		if (*fmt=='%')
// OTHER PARAMETERS
			switch(*++fmt) {
			case 'd':
				n+=itoa(va_arg(ap,int),10,f);
				break;
			case 'x':
				n+=itoa(va_arg(ap,int),16,f);
				break;
			case 's':
				s=va_arg(ap,char*);
				while (putc(*s++,f))
					n++;
				break;
			}
		else {
			putc(*fmt,f);
			n++;
		}
	return n;
}

printf(char *fmt, ...) {
	va_list	ap;
	int	n;
	va_start(ap,fmt);
	n=vfprintf(stdout,fmt,ap);
	va_end(ap);
	return n;
}

fprintf(FILE *f, char *fmt, ...) {
	va_list	ap;
	int	n;
	va_start(ap,fmt);
	n=vfprintf(f,fmt,ap);
	va_end(ap);
	return n;
}
