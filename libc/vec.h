#ifndef VEC_H
#define VEC_H

#define newvec()	((void*)(2+(int*)calloc(2,sizeof(int))))
#define freevec(v)	((v)? (free(metavec(v)),0): 0)
#define catvec(v,x)	((v)? ((v)=growvec((v),sizeof *(v)),\
				(v)[metavec(v)[0]++]=(x),(v)): (v))
#define lenvec(v)	((v)? metavec(v)[0]: 0)
#define capvec(v)	((v)? metavec(v)[1]: 0)
#define metavec(v)	((v)? (int*)(v)-2: 0)
static void*
growvec(void *v, size_t sz) {
	if (lenvec(v)+1 >= capvec(v))
		v=2+(int*)realloc(metavec(v),
			sizeof(int)*2 + (metavec(v)[1]+=32)*sz);
	return v;
}

#endif
