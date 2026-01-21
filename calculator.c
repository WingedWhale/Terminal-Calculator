#include "calculator.h"

// REMOVE WHEN DONE
#include <stdio.h>

void skip_whitespace(char **s)
{
	while (**s == ' ') {
		(*s)++;
	}
}

double parse_number(char **s, int *out)
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

double parse_primary(char **s, int *out)
{
	double number = 0;

	skip_whitespace(s);
	
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

double parse_power(char **s, int *out)
{
	double base = parse_primary(s, out);

	double exponent = 0;

	skip_whitespace(s);

	if (**s == '^') {
		(*s)++;
		skip_whitespace(s);
		exponent = parse_power(s, out);
	} else {
		return base;
	}

	if (*out != 0) return 0;

	return pow(base, exponent);
}

double parse_term(char **s, int *out)
{
	double number = parse_power(s, out);

	if (*out != 0) return 0;

	skip_whitespace(s);

	while (**s == '*' || **s == '/') {
		if (**s == '*') {
			(*s)++;
			number *= parse_power(s, out);
			if (*out != 0) return 0;
		}
		else {
			(*s)++;
			double rhs = parse_power(s, out);
			if (rhs == 0) {
				*out = -1;
				return 0;
			}
			number /= rhs;
			if (*out != 0) return 0;
		}

		skip_whitespace(s);
	}

	return number;
}

double parse_expression(char **s, int *out)
{
	double number = parse_term(s, out);

	if (*out != 0) return 0;

	skip_whitespace(s);

	while (**s == '+' || **s == '-') {
		if (**s == '+') {
			(*s)++;
			number += parse_term(s, out);
			if (*out != 0) return 0;
		}
		else {
			(*s)++;
			number -= parse_term(s, out);
			if (*out != 0) return 0;
		}

		skip_whitespace(s);
	}

	return number;
}
