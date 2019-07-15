#ifndef __SIMMEM_H__
#define __SIMMEM_H__

#include "octa.h"

typedef struct {
    tetra tet;
} mem_tetra;

typedef struct mem_node_struct {
    octa loc;
    tetra stamp;
    struct mem_node_struct *left, *right;
    mem_tetra dat[512];
} mem_node;

mem_tetra *mem_find ARGS((octa *));
mem_node *new_mem ARGS((void));

void panic ARGS((char *));
void print_hex ARGS((octa *));

#endif  /* __SIMMEM_H__ */
