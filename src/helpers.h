#ifndef constants_h
#define constants_h

/*
 *	Helper functions and variables
 */

#define	ERR	-1

/* For readability, since bool type was introduced in C99 */
#define	BOOL	unsigned char
#define	TRUE	1U
#define	FALSE	0U

/*
 *	Error handling functions:
 *		- one generic
 *		- one for functions with errno
 */
#define	_ERR(msg, r)	do { fprintf(stderr, msg); return r; } while(0)
#define	_ERR_P(msg, r)	do { perror(msg); return r; } while(0)

#endif