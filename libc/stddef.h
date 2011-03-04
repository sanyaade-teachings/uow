#ifndef STDDEF_H
#define STDDEF_H

#define NAME_MAX	256
#define PATH_MAX	256

#ifndef NULL
#define NULL		((void*)0)
#endif

#define offsetof(t,m)	(&((t*)0)->m - 0)
typedef unsigned	size_t;
typedef int		ptrdiff_t;

#endif
