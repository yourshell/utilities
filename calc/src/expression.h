/**
 *  @Name
 *  Math expression evaluator header
 *  
 *  @Description
 *  This header contains all necessary functions for parse and evaluate an expression.
 * */



#ifndef _STDIO_H
#include <stdio.h>
#endif


#ifndef _STDLIB_H
#include <stdlib.h>
#endif


#ifndef _STRING_H
#include <string.h>
#endif


#ifndef _CTYPE_H
#include <ctype.h>
#endif


// Structures
#include "structures/number-stack.h"
#include "structures/char-stack.h"


// Colors and styles
#define NC  "\x1B[0m"
#define RED "\x1B[31m"
#define HEADER "\033[95m"



/**
 *  @Synopsis
 *  int precedence(char operator);
 *
 *  @Description
 *  Set the precedence of operations.
 *
 *  @param operator: Operator symbol
 *  @type operator: char
 *
 *  @return: The precedence of given operator
 *  @rtype: int
 */
int precedence(char operator) {
	if(operator == '+' || operator == '-')
		return 1;
	if(operator == '*' || operator == '/')
		return 2;
	if(operator < 0)
		return 3;
	return -1;
}



/**
 *  @Synopsis
 *  void apply_operator(NumberStack **stack, char operator);
 *
 *  @Description
 *  Applying operator for numbers on stack.
 *
 *  @param stack: Stack where do we get the values from
 *  @type stack: NumberStack**
 *  @param operator: Operator symbol
 *  @type operator: char
 *
 *  @return: `side effect`: Pop elements from stack of numbers, apply operator to them and push to the stack
 */
void apply_operator(NumberStack **stack, char operator) {
	if(operator < 0 ) {                 // If its unary operator
		double x = number_pop(*stack);
		switch(-operator) {
			case '+': number_push(*stack, x); break;
			case '-': number_push(*stack, -x); break;
		}
	} else {                            // If its arithmetic operator
		double y = number_pop(*stack);
		double x = number_pop(*stack);
		if(operator == '/' && y == 0) {
			printf("%sError: Division by zero%s\n", RED, NC);
		}
		switch(operator) {
			case '+': number_push(*stack, x + y); break;
			case '-': number_push(*stack, x - y); break;
			case '*': number_push(*stack, x * y); break;
			case '/': number_push(*stack, x / y); break;
		}
	}
}



/**
 *  @Synopsis
 *  int is_unary(char c);
 *
 *  @Description
 *  Checks if char is unary operator.
 *
 *  @param c: Char to be checked
 *  @type c: char
 *
 *  @return: True (1) if char is unary operator and False (0) otherwise
 *  @rtype: int
 */
int is_unary(char c) {
	return c == '+' || c == '-';
}



/**
 *  @Synopsis
 *  int is_operator(char c);
 *
 *  @Description
 *  Checks if a char is an arithmetic operator.
 *
 *  @param c: Char to be checked
 *  @type c: char
 *
 *  @return: True (1) if char is arithmetic operator and False (0) otherwise
 *  @rtype: int
 */
int is_operator(char c) {
	return c == '+' || c == '-' || c == '*' || c == '/'; 
}



/**
 *  @Synopsis
 *  int is_delimiter(char c);
 *
 *  @Description
 *  Checks if a char is delimiter.
 *
 *  @param c: Char to be checked
 *  @type c: char
 *
 *  @return: True (1) if char is delimiter and False (0) otherwise
 *  @rtype: int
 */
int is_delimiter(char c) {
	return c == ' ' || c == '\t' || c == '\v';
}



/**
 *  @Synopsis
 *  void check_brackets(char *expression)
 *
 *  @Description
 *  Exception for brackets match. If open brackets not equal to close brackets prints error message.
 *
 *  @param expression: Expression string
 *  @type expression: char*
 *
 *  @return: `side effect`: Exception message
 */
void check_brackets(char *expression) {
	int open_brackets = 0, close_brackets = 0;
	int len = strlen(expression);

	for(int i = 0; i < len; i++) {
		if(expression[i] == '(')
			open_brackets++;
		else if(expression[i] == ')')
			close_brackets++;
	}

	if(open_brackets != close_brackets) {
		printf("%sError: Number of opening brackets not equal to number of closing brackets%s\n", RED, NC);
	}
}



/**
 *  @Synopsis
 *  double evaluate(char *expression);
 *
 *  @Description
 *  Evaluating the expression.
 *
 *  @param expression: Given expression
 *  @type expression: char*
 *
 *  @return: The result of expression
 *  @rtype: double
 */
double evaluate(char *expression) {
	check_brackets(expression);                 // Checks brackets match
    NumberStack *values = create_number_stack(BUFSIZ);
	CharStack *ops = create_char_stack(BUFSIZ);
	int i, len = strlen(expression);
	int may_be_unary = 0, break_point = 0;


	for(i = 0; i < len; i++) {
		if(is_delimiter(expression[i])) {       // Current char from expression is delimiter
			continue;
		} else if(expression[i] == '(') {	    // Current char from expression is open bracket
			char_push(ops, expression[i]);
			may_be_unary = 1;
		} else if(isdigit(expression[i])) {     // Current char from expression is number
			char val[BUFSIZ] = "";
			while(i < len && (isdigit(expression[i]) || expression[i] == '.')) {
				strncat(val, &expression[i], 1);
				i++;
			}
			number_push(values, atof(val));
			i--;
			may_be_unary = 0;
		} else if(expression[i] == ')') {       // Current char from expression is close bracket
			while(!char_is_empty(ops) && char_peek(ops) != '(') {
				char op = char_pop(ops);
				apply_operator(&values, op);
			}
			if(!char_is_empty(ops))
				char_pop(ops);
			may_be_unary = 0;
		} else if(is_operator(expression[i])) { // Current char from expression is operator
			char current_operator = expression[i];
			if(may_be_unary && is_unary(current_operator))
				current_operator = -current_operator;
			while(!char_is_empty(ops) && (
						(current_operator >= 0 && precedence(char_peek(ops)) >= precedence(current_operator)) ||
						(current_operator < 0 && precedence(char_peek(ops)) > precedence(current_operator))
						)) {
				char op = char_pop(ops);
				apply_operator(&values, op);
			}
			char_push(ops, current_operator);
			may_be_unary = 1;
		} else {                                // Current char from expression is unacceptable value for expression
			printf("%sError: Bad input value %c%s\n", RED, expression[i], NC);
            continue;
		}
	}

	while(!char_is_empty(ops) && !break_point) {
		char op = char_pop(ops);
		apply_operator(&values, op);
	}

	if(!break_point)
		return number_pop(values);
	else
		exit(1);
}
