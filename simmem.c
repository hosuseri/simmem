#include <stdlib.h>
#include <stdio.h>
#include "simmem.h"

tetra priority = 314159265;
mem_node *mem_root, *last_mem;

int main()
{
    int i;
    octa loc;
    tetra t;
    mem_tetra *p;

    mem_root = new_mem();
    mem_root->loc.h = 0x40000000;
    last_mem = mem_root;

    loc.l = loc.h = 0;
    for (i=0; i < 2097152; i++) {
	t = loc.l;
	loc.l += 0x800;
	if (loc.l <= t)
	    loc.h++;
#if 0
	print_hex(&loc);
	putchar('\n');
#endif
	fflush(stdout);
	mem_find(&loc);
    }
    for (i=0; i < 32; i++) {
	t = loc.l;
	loc.l += 0x800;
	if (loc.l <= t)
	    loc.h++;
	p = mem_find(&loc);
	{
	    unsigned long long hgn = (unsigned long long)p;
	    printf(
		"0x%08lx%08lx\n",
		(unsigned long)((hgn >> 32) & 0xFFFFFFFFLU),
		(unsigned long)(hgn & 0xFFFFFFFFLU));
	}
	fflush(stdout);
    }
    return 0;
}

mem_tetra *mem_find(addr)
octa *addr;
{
    octa key;
    register int offset;
    register mem_node *p = last_mem;

    key.h = addr->h;
    key.l = addr->l & 0xfffff800;
    offset = addr->l & 0x7fc;
    if (p->loc.l != key.l || p->loc.h != key.h) {
	register mem_node **q;

	for (p=mem_root; p; ) {
	    if (key.l == p->loc.l && key.h == p->loc.h)
		goto found;
	    if ((key.l < p->loc.l && key.h <= p->loc.h) ||
		key.h < p->loc.h)
		p = p->left;
	    else
		p = p->right;
	}
	for (p=mem_root, q=&mem_root; p && p->stamp < priority; p=*q)
	    if ((key.l < p->loc.h && key.h <= p->loc.h) ||
		key.l < p->loc.h)
		q = &p->left;
	    else
		q = &p->right;
	*q = new_mem();
	(*q)->loc = key;
	{
	    register mem_node **l, **r;

	    l = &(*q)->left;
	    r = &(*q)->right;
	    while (p) {
		if ((key.l < p->loc.h && key.h <= p->loc.h) ||
		    key.h < p->loc.h) {
		    *r = p;
		    r = &p->left;
		    p = *r;
		} else {
		    *l = p;
		    l = &p->right;
		    p = *l;
		}
	    }
	    *l = *r = NULL;
	}
	p = *q;
    found:
	last_mem = p;
    }
    return &p->dat[offset >> 2];
}

mem_node *new_mem()
{
    register mem_node *p;

    p = (mem_node *)calloc(1, sizeof(mem_node));
    if (!p)
	panic("Can't allocate any more memory");
    p->stamp = priority;
    priority += 0x9e3779b9;  /* floor(2.0**32 * (phi-1.0)) */
    return p;
}

void panic(s)
char *s;
{
    fprintf(stderr, "%s\n", s);
}

void print_hex(o)
octa *o;
{
    if (o->h)
	printf("%x%08x", o->h, o->l);
    else
	printf("%x", o->l);
}
