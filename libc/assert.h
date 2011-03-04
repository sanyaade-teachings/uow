#ifndef ASSERT_H
#define ASSERT_H

#ifdef NDEBUG
#define assert(e)
#else
#define assert(e)\
	do\
		if (!e) {\
			fprintf(stderr,"assert failed %s %d: %s\n",\
				__FILE,__LINE,#e);\
			abort();\
		}\
	while(0)
#endif

#endif