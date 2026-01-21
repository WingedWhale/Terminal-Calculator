#include "calculator.h"

#include <math.h>

void skip_whitespace(const char **s)
{
	while (**s == ' ') {
		(*s)++;
	}
}

double parse_number(const char **s, int *out)
{
	double number = 0;
	bool decimal = false;
	int decimal_level = 10;

	while ((**s >= '0' && **s <= '9') || **s == '.') {
		if (**s == '.') {
			if (decimal) {
				// HANDLE ERROR
			}
			decimal = true;
			(*s)++;
			continue;
		}
		if (!decimal) {
			number = 10 * number + (**s - '0');
		} else {
			number += (double)(**s - '0') / decimal_level;
			decimal_level *= 10;
		}
		(*s)++;
	}
	return number;
}

double parse_primary(const char **s, int *out)
{
	double number = 0;
	
	if (**s == '(') {
		(*s)++;

		number = parse_expression(s, out);

		if (**s != ')') {
			// HANDLE ERROR
		} else {
			(*s)++;
		}
	} else if ((**s >= '0' && **s <= '9') || **s == '.') {
		number = parse_number(s, out);
	} else {
		// HANDLE ERROR
	}

	return number;
}

double parse_power(const char **s, int *out)
{
	skip_whitespace(s);

	double base = parse_primary(s, out);

	printf("base = %f\n", base);
	
	double exponent = 0;

	if (**s == '^') {
		(*s)++;
		skip_whitespace(s);
		exponent = parse_power(s, out);

		printf("exponent = %f\n", exponent);
	} else {
		return base;
	}

	if (*out != 0) return 0;

	return pow(base, exponent);
}

double parse_term(const char **s, int *out)
{
	double number = parse_power(s, out);

	return number;
}

double parse_expression(const char **s, int *out)
{
	double number = parse_term(s, out);

	return number;
}
