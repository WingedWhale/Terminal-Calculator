#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"

int main()
{
	size_t size = 256;

	char *input = malloc(size * sizeof(char));

	while (1) {
		printf(": ");

		if (fgets(input, size, stdin) == NULL) {
			printf("Input error.\n");
			return 1;
		}

		if (*input == 'q') {
			break;
		}

		CalcError out = SUCCESS;

		char *walker = input;

		double value = parse_expression(&walker, &out);

		switch (out) {
			case SUCCESS:
				printf("%f\n", value);
				break;
			case ERR_DIV_ZERO:
				printf("ERROR: Cannot divide by zero.\n");
				break;
			case ERR_SYNTAX:
				printf("ERROR: Invalid syntax.\n");
				break;
			case ERR_PAREN:
				printf("ERROR: Improper parentheses.\n");
				break;
			case ERR_UNKNOWN:
				printf("ERROR: Unknown symbol.\n");
				break;
		}
	}

	free(input);

	return 0;
}
