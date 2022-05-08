/**
 * @Name
 * Simple terminal calculator
 *
 * @Desciption
 * Example of how to work with expression evaluator.
 * */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expression.h"



char *readline(void);
void input(void);


//! main
int main(void) {
    input();
    return 0;
}



/**
 *  @Synopsis
 *  char* readline(void);
 *
 *  @Desciption
 *  Read input line from stdin.
 *
 *  @return: Given string from stdin
 *  @rtype: char*
 */
char *readline(void) {
    int bufsize = BUFSIZ;
    int position = 0;
    char *buffer = malloc(sizeof(char)*bufsize);
    int c;

    if(!buffer) {
        fprintf(stderr, "calc.c: Allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        c = getchar();

        if(c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else if(c == EOF) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            buffer[position] = c;
        }
        position++;

        if(position >= bufsize) {
            bufsize += BUFSIZ;
            buffer = realloc(buffer, bufsize);
            if(!buffer) {
                fprintf(stderr, "calc: Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}



/**
 *  @Synopsis
 *  void input(void)
 *
 *  @Desciption
 *  Example of express evaluator usage.
 */
void input(void) {
    char *expression;

    printf("%scalc.c\n", HEADER);
    printf("Type some expressions and get results.\n");
    printf("To finish entering expressions just type - 'end'%s\n\n\n", NC);

    while(1) {
        printf(">>> ");
        expression = readline();
        if(strcmp(expression, "end")) {
            printf("%f\n", evaluate(expression));
        } else {
            break;
        }
    }
}
