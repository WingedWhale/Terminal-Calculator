#include <stdio.h>

#include "calculator.h"

int main()
{
	const char *number = "2 ^ 3";
	
	printf("string = %s\n", number);

	int out = 0;

	double value = parse_power(&number, &out);
	
	printf("value = %f\n", value);
	printf("out = %d\n", out);

	return 0;
}
