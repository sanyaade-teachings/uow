#include <stdlib.h>
#include <vec.h>
#include <unistd.h>
#include <fcntl.h>
#include <windows.h>

static void	(**__atexit)(void);
static char	*envstr;

void*
malloc(size_t sz) {
	return HeapAlloc(GetProcessHeap(),0,sz);
}

void*
calloc(size_t n, size_t sz) {
	return HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,n*sz);
}

void*
realloc(void *buf, size_t sz) {
	return HeapReAlloc(GetProcessHeap(),0,buf,sz);
}

void
free(void *buf) {
	HeapFree(GetProcessHeap(),0,buf);
}

size_t
_msize(void *buf) {
	return HeapSize(GetProcessHeap(),0,buf);
}

void
_exit(code) {
	ExitProcess(code);
}

void
exit(code) {
	int	i;
	i=lenvec(__atexit);
	while (i-->0)
		__atexit[i]();
	_exit(code);
}

atexit(void (*todo)(void)) {
	catvec(__atexit,todo);
	return 0;
}

void
abort() {
	write(2,"abnormal program termination",28);
//	SUPPOSED TO CALL raise(SIGABRT)
	exit(3);
}

abs(n) {
	return n<0? -n: n;
}

div_t
div(n,d) {
	div_t	x;
	x.quot=n/d;
	x.rem=n%d;
	return x;
}

ldiv_t
ldiv(long n, long d) {
	ldiv_t	x;
	x.quot=n/d;
	x.rem=n%d;
	return x;
}

atoi(const char *s) {
	int	x=0;
	while (*s && isdigit(*s))
		x=(x*10)+(*s-'0');
	return x;
}

long
labs(long n) {
	return n<0? -n: n;
}

long
strtol(const char *s, char **endp, int base) {
	static char	invdigit[256];
	static char	*digit="0123456789abcdef";
	long		x=0;
	int		i;
	if (!invdigit['0'])
		for (i=0; digit[i]; i++)
			invdigit[digit[i]]=i;
	while (*s && memchr(digit,*s,base))
		x=(x*base)+invdigit[*s&255];
	endp && (*endp=(char*)s);
	return x;
}

unsigned long
strtoul(const char *s, char **endp, int base) {
	return strtol(s,endp,base);
}

char*
getenv(const char *name) {
	int	sz;
	free(envstr);
	sz=GetEnvironmentVariable(name,0,0);
	if (!sz && GetLastError()==ERROR_ENVVAR_NOT_FOUND)
		return 0;
	envstr=malloc(sz+1);
	GetEnvironmentVariable(name,envstr,sz+1);
	return envstr;
}

system(char *cmd) {
	static char		*cmdspec="cmd /C ";
	char			*s,*whole;
	PROCESS_INFORMATION	pi;
	STARTUPINFO		si;
	int			ret;
	
	memset(&si,0,sizeof si);
	si.cb=sizeof si;
	si.dwFlags=STARTF_USESTDHANDLES;
	si.hStdInput=GetStdHandle(STD_INPUT_HANDLE);
	si.hStdOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError=GetStdHandle(STD_ERROR_HANDLE);
	
	if (!cmd) {
		if (CreateProcess(0,cmdspec,0,0,1,0,0,0,&si,&pi)) {
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			return 1;
		}
		return 0;
	}
	
	whole=newvec();
	for (s=cmdspec; *s; s++)
		catvec(whole,*s);
	for (s=cmd; *s; s++)
		catvec(whole,*s);
	catvec(whole,0);
	if (CreateProcess(0,whole,0,0,1,0,0,0,&si,&pi)) {
		WaitForSingleObject(pi.hProcess,INFINITE);
		GetExitCodeProcess(pi.hProcess,&ret);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
		return ret;
	}
	return 0;
}

void
_searchenv(const char *fn, const char *paths, char *outp) {
	char	*p,*d,*list=0;
	int	fd;
	
	if (!paths)
		goto fail;
	
	list=strdup(paths);
	p=strtok(list,";");
	if (!p) {
		*outp=0;
		goto end;
	}
	
	do {
		d=outp;
		while (*p)
			*d++=*p++;
		*d++='/';
		for (p=(char*)fn; *p; p++)
			*d++=*p;
		*d=0;
		if ((fd=open(outp,O_RDONLY)) >= 0) {
			close(fd);
			goto end;
		}
	} while (p=strtok(0,";"));
fail:
	*outp=0;
end:
	free(list);
}

void
searchenv(const char *fn, const char *var, char *outp) {
	_searchenv(fn,getenv(var),outp);
}

__initstdlib() {
	__atexit=newvec();
}
