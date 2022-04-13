#ifndef _STDIO_H
#include <stdio.h>
#endif


#ifndef _STDLIB_H
#include <stdlib.h>
#endif


/* ******************************** */
/* Stack structure with char field  */
/* ******************************** */

typedef struct CharStack {
	int top;
	unsigned int capacity;
	char *array;
} CharStack;


/* Initialize CharStack */
CharStack *create_char_stack(unsigned int capacity) {
	CharStack *s = (CharStack *)malloc(sizeof(CharStack));
	s->capacity = capacity;
	s->top = -1;
	s->array = (char *)malloc(s->capacity * sizeof(char));
	return s;
}


/* Checks for stack overflow */
int char_is_full(CharStack *s) {
	return s->top == (int)(s->capacity - 1);
}


/* Checks the stack for fullness */
int char_is_empty(CharStack *s) {
	return s->top == -1;
}


/* Push item to stack */
void char_push(CharStack *s, char item) {
	if(char_is_full(s))
		return;
	s->array[++s->top] = item;
}


/* Pop item from stack */
char char_pop(CharStack *s) {
	if(char_is_empty(s)) {
		printf("error: CharStack is empty\n");
		exit(1);
	}
	return s->array[s->top--];
}


/* Show item from stack */
char char_peek(CharStack *s) {
	if(char_is_empty(s)) {
		printf("error: CharStack is empty\n");
		exit(1);
	}
	return s->array[s->top];
}
