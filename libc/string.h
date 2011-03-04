#include <stddef.h>
extern size_t
	strlen(const char *s),
	strcspn(const char *big, const char *cset),
	strspn(const char  *big, const char *set);
extern
	memcmp(const void *a, const void *b, size_t len),
	strncmp(const char *a, const char *b, size_t len),
	strcmp(const char *a, const char *b);
extern void
	*memchr(const void *big, int c, size_t len),
	*memcpy(void *a, const void *b, size_t len),
	*memmove(void *a, const void *b, size_t len),
	*memset(void *dst, int c, size_t len);
extern char
	*strchr(const char *big, int c),
	*strrchr(const char *big, int c),
	*strstr(const char *big, const char *sub),
	*strcat(char *pre, char *post),
	*strcpy(char *dst, const char *src),
	*strdup(const char *src),
	*strncpy(char *dst, char *src, size_t len),
	*strpbrk(const char *big, const char *cset),
	*strtok(char *src, const char *delim);
	
