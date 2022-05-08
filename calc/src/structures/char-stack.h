/**
 *  @Name
 *  Operators (char) stack header
 *
 *  @Description
 *  Definition of operator stack.
 * */



#ifndef _STDIO_H
#include <stdio.h>
#endif


#ifndef _STDLIB_H
#include <stdlib.h>
#endif



/**
 *  @Description
 *  Stack of operator definition.
 * */
typedef struct CharStack {
    int top;                    // Current number of elements on stack
    unsigned int capacity;      // Stack size
    char *array;                // Array of double values
} CharStack;



/**
 *  @Synopsis
 *  CharStack* create_char_stack(unsigned int capacity);
 *
 *  @Description
 *  Initializes a new stack for operators.
 *
 *  @param capacity: Initial stack size
 *  @type capacity: unsigned int
 *
 *  @return: Empty stack for operators
 *  @rtype: CharStack*
 * */
CharStack *create_char_stack(unsigned int capacity) {
    CharStack *s = (CharStack *)malloc(sizeof(CharStack));
    s->capacity = capacity;
    s->top = -1;                // No items yet
    s->array = (char *)malloc(s->capacity * sizeof(char));
    return s;
}



/**
 *  @Synopsis
 *  int char_is_full(CharStack *s);
 *
 *  @Description
 *  Checks the stack for overflow.
 *
 *  @param s: Stack to be checked
 *  @type s: CharStack*
 *
 *  @return: True (1) if stack is full and False (0) otherwise
 *  @rtype: int
 * */
int char_is_full(CharStack *s) {
    return s->top == (int)(s->capacity - 1);
}



/**
 *  @Synopsis
 *  int char_is_empty(CharStack *s);
 *
 *  @Description
 *  Checks the stack is empty.
 *
 *  @param s: Stack to be checked
 *  @type s: CharStack*
 *
 *  @return: True (1) if stack is empty and False (0) otherwise
 *  @rtype: int
 * */
int char_is_empty(CharStack *s) {
    return s->top == -1;
}



/**
 *  @Synopsis
 *  void char_push(CharStack *s, char item);
 *
 *  @Description
 *  Pushing new item to the top of the stack.
 *
 *  @param s: Stack on which the new item is added
 *  @type s: CharStack*
 *  @param item: Value that is added to the stack
 *  @type item: char
 *
 *  @return: `side effect`: Added new item to the stack
 * */
void char_push(CharStack *s, char item) {
    if(char_is_full(s))
        return;
    s->array[++s->top] = item;
}



/**
 *  @Synopsis
 *  char char_pop(CharStack *s);
 *
 *  @Description
 *  Get the item from the top of the stack and delete it from array. (pop it)
 *
 *  @param s: Stack where we will take value from
 *  @type s: CharStack*
 *
 *  @return: Top value from the stack
 *  @rtype: char 
 * */
char char_pop(CharStack *s) {
    if(char_is_empty(s)) {
        printf("Error: CharStack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->array[s->top--];
}



/**
 *  @Synopsis
 *  char char_peek(CharStack *s);
 *
 *  @Description
 *  View the item from the top of the stack.
 *
 *  @param s: Stack where we will take value from
 *  @type s: CharStack*
 *
 *  @return: Top value from the stack
 *  @rtype: char 
 * */
char char_peek(CharStack *s) {
    if(char_is_empty(s)) {
        printf("Error: CharStack is empty\n");
        exit(EXIT_FAILURE);
    }
    return s->array[s->top];
}
