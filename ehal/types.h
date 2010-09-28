#ifndef __TYPES_H
#define __TYPES_H

/* custom types */
typedef unsigned char		u08;
typedef unsigned short int	u16;
typedef unsigned long int	u32;
typedef unsigned long long	u64;

typedef signed char		s08;
typedef signed short int	s16;
typedef signed long int		s32;
typedef signed long long	s64;

#define ARRAY_SIZE(x)	(sizeof(x) / sizeof(x[0]))

#define GLUE2( x, y ) x ## y
#define GLUE( x, y ) GLUE2( x, y )

#endif
