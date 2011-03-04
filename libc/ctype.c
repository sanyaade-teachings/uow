#include <ctype.h>
enum {
	LO=1,
	UP=2,
	DIG=4,
	SP=8,
	PUN=16
};

static char	tab[256];
static char	utab[256];
static char	ltab[256];

isalnum(c) {
	return tab[c&255] & (LO|UP+DIG);
}
isalpha(c) {
	return tab[c&255] & (LO|UP);
}
iscntrl(c) {
	return c<32;
}
isdigit(c) {
	return tab[c&255] & (DIG);
}
isgraph(c) {
	return isprint(c) && c!=' ';
}
islower(c) {
	return tab[c&255] & (LO);
}
isprint(c) {
	return c>=32 && c<127;
}
ispunct(c) {
	return tab[c&255] & (PUN);
}
isspace(c) {
	return tab[c&255] & (SP);
}
isupper(c) {
	return tab[c&255] & (UP);
}
toupper(c) {
	return utab[c&255];
}
tolower(c) {
	return ltab[c&255];
}

__initctype() {
	char	*s;
	int	i;
	for (i='a'; i<='z'; i++)
		tab[i] |= LO;
	for (i='A'; i<='Z'; i++)
		tab[i] |= UP;
	for (i='0'; i<='9'; i++)
		tab[i] |= DIG;
	for (s="!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"; *s; s++)
		tab[*s] |= PUN;
	for (i=9; i<14; i++)
		tab[i] |= SP;
	tab[' ']=SP;
	for (i=0; i<256; i++)
		utab[i]=islower(i)? i-32: i;
	for (i=0; i<256; i++)
		ltab[i]=isupper(i)? i+32: i;
}
