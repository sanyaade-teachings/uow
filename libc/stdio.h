#ifndef STDIO_H
#define STDIO_H

#include <stddef.h>

typedef  struct {
	int	fd;
	int	err;
	int	eof;
	int	mod;
} FILE;

#define MAX_FILE	255
#define EOF		-1
#define getc(f)		fgetc(f)
#define putc(c,f)	fputc(c,f)
#define getchar()	getc(stdin)
#define putchar(c)	putc(c,stdout)

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2

FILE	*stdin,*stdout,*stderr;
FILE	*fopen(const char *name, const char *mode),
	*fdopen(int fd, const char *mode);
	
extern
	fclose(FILE *f),
	_fcloseall(),
	fflush(FILE *f),
	fgetc(FILE *f),
	feof(FILE *f),
	ferror(FILE *f),
	fputc(int c, FILE* f),
	fputs(const char *s, FILE *f),
	puts(const char *s),
	fread(void *buf, int n, int sz, FILE *f),
	fwrite(void *buf, int n, int sz, FILE *f);
extern char
	*fgets(char *buf, size_t max, FILE *f),
	*gets(char *buf);
void
	clearerr(FILE *f);
	
#endif
