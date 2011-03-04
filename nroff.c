#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	C(AB)	*lp==#AB[0] && lp[1]==#AB[1] && (lp+=3)
#define	C1(A)	*lp==#A[0] && (!lp[1] || lp[1]==' ') && (lp+=2)

FILE	*f;
char	line[1024],*lp;
char	buf[1024],*bp;
char	*wp;
int	wid=80;
int	ind;
int	tab;
int	nc;

get() {
	return fgets(line,sizeof line,f)!=0;
}

flush(int wrap) {
	if (!wp || !wrap)
		wp=bp;
	fwrite(buf,1,wp-buf,stdout);
	memset(buf,' ',ind);
	memcpy(buf+ind,wp,bp-wp);
	bp=buf+ind + (bp-wp);
	wp=0;
	nc=0;
	putchar('\n');
}

isbrk(int c) {
	return isspace(c) || ispunct(c);
}

out(char *txt) {
	while (*txt) {
		if (isspace(*txt))
			wp=bp;
		else if (ispunct(*txt))
			wp=bp+1;
		if ((bp-buf) >= wid-1)
			flush(!isbrk(*txt));
		if (*txt=='\\' && txt++) {
			if (*txt=='-' && txt++)
				*bp++='-';
		}
//		TAB
		*bp++=*txt++;
	}
}

doline() {
	int	n,notab;
	
	notab=0;
	lp=line;
	lp[strcspn(lp,"\n")]=0;
	if (*lp!='.') {
		if (bp!=buf+ind)
			out(" ");
		out(lp);
		return 0;
	}
	lp++;
	
	if (C(TH)) {
		flush(0);
		out(lp);
		flush(0);
	} else if (C(SH)) {
		ind=0;
		flush(0);
		out(lp);
		ind=8;
		flush(0);
	} else if (C1(I) || C1(B)) {
		if (bp!=buf+ind && !tab)
			out(" ");
		out(lp);
	} else if (C1(P))
		flush(0);
	else if (C(PP)) {
		ind=8;
		flush(0);
	} else if (C(br))
		flush(0);
	else if (C(TP)) {
		ind=8;
		flush(0);
		n=atoi(lp);
		ind=8 + (n? n: 8);
		get();
		doline();
		if ((bp-buf)>=ind)
			flush(0);
		else for (n=ind-(bp-buf); n; n--)
			out(" ");
	} else if (C(./));	
	return 1;
}

main(int argc, char **argv) {
	for (argv++; *argv; argv++)
		if (**argv=='-')
			;
		else if (f=fopen(*argv,"r")) {
			bp=buf;
			tab=0;
			while (get())
				doline();
			flush(0);
			fclose(f);
		} else
			fprintf(stderr,
				"nroff: cannot open %s\n",
				*argv);
	return 0;
}
