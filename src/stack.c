#include <stack.h>

stack_t *stack_init(int max_size) {
	stack_t *s = (stack_t *) malloc(sizeof(stack_t));
	s->size = 0;
	s->max_size = max_size;
	s->elmts = (int *) malloc(sizeof(int) * max_size);

	return s;
}

bool is_not_empty(stack_t *s) {
	return (bool) s->size != 0;
}

bool push(stack_t *s, int elmt) {
	if(s->size < s->max_size) {
		s->elmts[s->size++] = elmt;
		return true;
	}
	return false;
}

int pop(stack_t *s) {
	return s->elmts[--s->size];
}

void stack_destroy(stack_t *s) {
	free(s->elmts);
	free(s);
}
