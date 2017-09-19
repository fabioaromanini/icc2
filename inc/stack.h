#ifndef _STACK_H
#define _STACK_H

#include <stdlib.h>

#include <bool.h>

typedef struct {
	int *elmts;
	int size;
	int max_size;
} stack_t;

stack_t *stack_init(int max_size);
bool is_empty(stack_t *s);
bool is_in_stack(stack_t *s, int element);
bool push(stack_t *s, int elmt);
int top(stack_t *s);
int pop(stack_t *s);
int get_elmnt_at(stack_t *s, int position);
void stack_destroy(stack_t *s);

#endif