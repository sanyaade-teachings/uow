/*
 * BUGS:
 *	atof
 *	strtod
 *	strxfrm
 *	bsearch
 *	qsort
 */

#ifndef STDLIB_H
#define STDLIB_H
 
#include <stddef.h>

typedef struct {
	int	quot;
	int	rem;
} div_t;

typedef struct {
	long	quot;
	long	rem;
} ldiv_t;

extern void
	free(void *buf),
	*calloc(size_t n, size_t sz),
	*malloc(size_t sz),
	*realloc(void *buf, size_t sz),
	_exit(int code),
	exit(int code),
	abort(),
	searchenv(const char *fn, const char *var, char *outp),
	_searchenv(const char *fn, const char *paths, char *outp);
extern
	atexit(void (*todo)(void)),
	system(char *cmd);
	abs(int n),
	atoi(const char *s);
extern long
	labs(long n),
	strtol(const char *s, char **endp, int base);
extern unsigned long
	strtoul(const char *s, char **endp, int base);
extern char*
	getenv(const char *name);
extern div_t	div(int n, int d);
extern ldiv_t	ldiv(long n, long d);

#endif
