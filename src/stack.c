#include <stack.h>

stack_t *stack_init(int max_size) {
	stack_t *s = (stack_t *) malloc(sizeof(stack_t));
	s->size = 0;
	s->max_size = max_size;
	s->elmts = (item_t *) malloc(sizeof(item_t) * max_size);

	return s;
}

bool is_empty(stack_t *s) {
	return (bool) (s->size  <= 0);
}

bool is_in_stack(stack_t *s, item_t element) {
	for(int i = 0; i < s->size; i++) {
		if(s->elmts[i] == element) return TRUE;
	}
	return FALSE;
}

bool push(stack_t *s, item_t element) {
	if(s->size < s->max_size) {
		s->elmts[(s->size)++] = element;
		return TRUE;
	}
	return FALSE;
}

item_t get_elmnt_at(stack_t *s, int position) {
	return s->elmts[position];
}

item_t pop(stack_t *s) {
	if(s->size == 0) return -1;
	else return s->elmts[--(s->size)];
}

item_t top(stack_t *s) {
	if(s->size == 0) return -1;
	else return s->elmts[s->size - 1];
}

void stack_destroy(stack_t *s) {
	free(s->elmts);
	free(s);
}
