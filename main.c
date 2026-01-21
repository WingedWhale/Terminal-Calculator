#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"

int main()
{
	size_t size = 256;

	char *input = malloc(size * sizeof(int));

	while (1) {
		printf(": ");

		if (fgets(input, size, stdin) == NULL) {
			printf("Input error.\n");
			return 1;
		}

		if (*input == 'q' && strlen(input) == 2) {
			break;
		}

		int out = 0;

		double value = parse_expression(&input, &out);
		
		printf("value = %f\n", value);
		printf("out = %d\n\n", out);
	}

	return 0;
}
