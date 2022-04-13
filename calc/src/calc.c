#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "expression.h"


#define BUFSIZE 256


char *readline(void);
void input(void);


int main(void) {
    input();
	return 0;
}


char *readline(void) {
    int bufsize = BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char)*bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "Calc: Allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "Calc: Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


void input(void) {
	char *expression;
    
    printf("calc.c\n");
    printf("Type some expressions and get results.\n");
	printf("To finish entering expressions just type - 'end'\n\n\n");

	while (1) {
		printf(">>> ");
        expression = readline();
		if (strcmp(expression, "end")) {
            printf("%f\n", evaluate(expression));
		} else {
			break;
        }
	}
}
