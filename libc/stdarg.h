/*
 *	BUGS:
 *		va_arg does not handle short or char
 *
 */
#ifndef STDARG_H
#define STDARG_H

#ifndef _VA_LIST_DEFINED
#define _VA_LIST_DEFINED
typedef void* va_list;
#endif

#define va_arg(ap,type) (*((type*)(ap))++)
#define va_end(ap)
#define va_start(ap,start) (ap=(char*)&start+(sizeof start))

#endif
