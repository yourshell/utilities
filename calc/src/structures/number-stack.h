/**
 * @Name
 * Number stack header
 *
 *  @Description
 *  Definition of number stack.
 * */


#ifndef _STDIO_H
#include <stdio.h>
#endif


#ifndef _STDLIB_H
#include <stdlib.h>
#endif



/**
 *  @Description
 *  Stack of number definition.
 * */
typedef struct NumberStack {
	int top;                    // Current number of elements on stack
	unsigned int capacity;      // Stack size
	double *array;              // Array of double values
} NumberStack;



/**
 *  @Synopsis
 *  NumberStack* create_number_stack(unsigned int capacity);
 *
 *  @Description
 *  Initializes a new stack for numbers.
 *
 *  @param capacity: Initial stack size
 *  @type capacity: unsigned int
 *
 *  @return: Empty stack for numbers
 *  @rtype: NumberStack*
 * */
NumberStack *create_number_stack(unsigned int capacity) {
	NumberStack *s = (NumberStack *)malloc(sizeof(NumberStack));
	s->capacity = capacity;
	s->top = -1;                // No items yet
	s->array = (double *)malloc(s->capacity * sizeof(double));
	return s;
}



/**
 *  @Synopsis
 *  int number_is_full(NumberStack *s);
 *
 *  @Description
 *  Checks the stack for overflow.
 *
 *  @param s: Stack to be checked
 *  @type s: NumberStack*
 *
 *  @return: True (1) if stack is full and False (0) otherwise
 *  @rtype: int
 * */
int number_is_full(NumberStack *s) {
	return s->top == (int)(s->capacity - 1);
}



/**
 *  @Synopsis
 *  int number_is_empty(NumberStack *s);
 *
 *  @Description
 *  Checks the stack is empty.
 *
 *  @param s: Stack to be checked
 *  @type s: NumberStack*
 *
 *  @return: True (1) if stack is empty and False (0) otherwise
 *  @rtype: int
 * */
int number_is_empty(NumberStack *s) {
	return s->top == -1;
}



/**
 *  @Synopsis
 *  void number_push(NumberStack *s, double item);
 *
 *  @Description
 *  Pushing new item to the top of the stack.
 *
 *  @param s: Stack on which the new item is added
 *  @type s: NumberStack*
 *  @param item: Value that is added to the stack
 *  @type item: double
 *
 *  @return: `side effect`: Added new item to the stack
 * */
void number_push(NumberStack *s, double item) {
	if(number_is_full(s))
		return;
	s->array[++s->top] = item;
}



/**
 *  @Synopsis
 *  double number_pop(NumberStack *s);
 *
 *  @Description
 *  Get the item from the top of the stack and delete it from array. (pop it)
 *
 *  @param s: Stack where we will take value from
 *  @type s: NumberStack*
 *
 *  @return: Top value from the stack
 *  @rtype: double
 * */
double number_pop(NumberStack *s) {
    if(number_is_empty(s)) {
        printf("Error: NumberStack is empty\n");
        exit(1);
    }
	return s->array[s->top--];
}
