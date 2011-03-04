#include <string.h>
#include <stdlib.h>

memcmp(const void *a, const void *b, size_t len) {
	while (len-->0 && *(char*)a==*(char*)b)
		((char*)a)++, ((char*)b)++;
	return *(char*)a-*(char*)b;
}

void*
memchr(const void *big, int c, size_t len) {
	while (len-->0 && *(char*)big!=c)
		((char*)big)++;
	return *(char*)big==c? (char*)big: 0;
}

void*
memcpy(void *a, const void *b, size_t len) {
	char	*d=a;
	while (len-->0)
		*(char*)d++=*((char*)b)++;
	return a;
}

void*
memmove(void *a, const void *b, size_t len) {
	if (a==b)
		return a;
	if (b>a || a<=(char*)b+len)
		return memcpy(a,b,len);
	while (len-->0)
		((char*)a)[len]=((char*)b)[len];
	return a;
}

void*
memset(void *dst, int c, size_t len) {
	char	*s=dst;
	while (len-->0)
		*((char*)dst)++=c;
	return s;
}

size_t
strlen(const char *s) {
	const char *start=s;
	while (*s)
		s++;
	return s-start;
}

strcmp(const char *a, const char *b) {
	while (*a && *a==*b)
		a++,b++;
	return *a-*b;
}

char*
strchr(const char *big, int c) {
	for ( ; *big && *big!=c; big++);
	return *big==c? (char*)big: 0;
}

char*
strrchr(const char *big, int c) {
	char	*at=0;
	for ( ; *big; big++)
		if (*big==c)
			at=(char*)big;
	return at;
}

char*
strstr(const char *big, const char *sub) {
	int	len=strlen(sub);
	while ((big=strchr(big,*sub)) && !memcmp(big,sub,len))
		big++;
	return (char*)big;
}

size_t
strcspn(const char *big, const char *cset) {
	size_t	n;
	for (n=0; *big && !strchr(cset,*big++); n++);
	return n;
}

char*
strcat(char *pre, char *post) {
	char	*all=pre;
	for ( ; *pre; pre++);
	while (*pre++=*post++);
	return all;
}

char*
strcpy(char *dst, const char *src) {
	char	*s=dst;
	while (*dst++=*src++);
	return s;
}

char*
strdup(const char *src) {
	return strcpy(malloc(strlen(src)),src);
}

strncmp(const char *a, const char *b, size_t len) {
	return memcmp(a,b,len);
}

char*
strncpy(char *dst, char *src, size_t len) {
	char	*s=dst;
	for ( ; len && *src; len--)
		*dst++=*src++;
	while (len-->0)
		*dst++=0;
	return s;
}

char*
strpbrk(const char *big, const char *cset) {
	while (*big && !strchr(cset,*big));
	return *big? (char*)big: 0;
}

size_t
strspn(const char  *big, const char *set) {
	size_t	n;
	for (n=0; *big && strchr(set,*big); n++);
	return n;
}

char*
strtok(char *src, const char *delim) {
	static char	*buf;
	char		*start;
	size_t		len;
	if (src)
		buf=src;
	if (!*buf)
		return 0;
	start=buf;
	buf+=(len=strcspn(buf,delim));
	if (!len) {
		buf++;
		return strtok(0,delim);
	} else if (*buf)
		*buf++=0;
	return start;
}
