#ifndef _STACK_H
#define _STACK_H

#include <stdlib.h>

#include <bool.h>

// since the memory usage is already theta of N^2 due 
// to the adjacency matrix,and the stack for the BFS
// is theta of N there is no need for a sofisticated
// stack dinamically alocated, with a more generic
// typing, even tough that would be my choice for a  longer
// project, specially with a higher level language
typedef struct {
	int *elmts;
	int size;
	int max_size;
} stack_t;

stack_t *stack_init(int max_size);
bool is_not_empty(stack_t *s);
bool push(stack_t *s, int elmt);
int pop(stack_t *s);
void stack_destroy(stack_t *s);

#endif