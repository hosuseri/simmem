#ifndef __OCTA_H__
#define __OCTA_H__

typedef enum {
    false, true
} bool;

typedef unsigned int tetra;

typedef struct {
    tetra h, l;
} octa;

typedef unsigned char byte;

#ifdef __STDC__
#define ARGS(list) list
#else
#define ARGS(list) ()
#endif

#endif  /*  __OCTA_H__ */
