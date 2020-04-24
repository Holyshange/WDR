#ifndef __BASE_TYPE_H__
#define __BASE_TYPE_H__


typedef unsigned char 			T_U8;
typedef unsigned short int 		T_U16;
typedef unsigned long int 		T_U32;
typedef unsigned long long int 	T_U64;
typedef signed char 			T_S8;
typedef signed short int 		T_S16;
typedef signed long int 		T_S32;
typedef signed long long int 	T_S64;

typedef T_U8 T_BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif
