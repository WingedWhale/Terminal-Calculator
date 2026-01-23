#include "calculator.h"

#ifndef M_PI
	#define M_PI 3.1415926535897932384626
#endif

void skip_whitespace(char **s)
{
	while (**s == ' ') {
		(*s)++;
	}
}

double parse_number(char **s, CalcError *out)
{
	double number = 0;
	bool decimal = false;
	int decimal_level = 10;

	while ((**s >= '0' && **s <= '9') || **s == '.') {
		if (**s == '.') {
			if (decimal) {
				*out = ERR_SYNTAX; // ERROR: duplicate decimal points
				return 0;
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

double parse_primary(char **s, CalcError *out)
{
	double number = 0;

	skip_whitespace(s);

	double unary = 1.0;

	if (**s == '-') {
		unary = -1.0;
		(*s)++;
	}
	
	if (**s == '(') {
		(*s)++;

		number = parse_expression(s, out);
		if (*out != SUCCESS) {
			return 0;
		}

		if (**s != ')') {
			*out = ERR_PAREN; // ERROR: Missing right parenthese
			return 0;
		} else {
			(*s)++;
		}
	} else if ((**s >= '0' && **s <= '9') || **s == '.') {
		number = parse_number(s, out);

		if (*out != SUCCESS) {
			return 0;
		}
	} else if ((**s >= 'a' && **s <= 'z') || (**s >= 'A' && **s <= 'Z')) {
		char str[64];
		size_t i = 0;
		while ((**s >= 'a' && **s <= 'z') || (**s >= 'A' && **s <= 'Z')) {
			str[i] = tolower(**s);
			i++;
			(*s)++;
		}

		str[i] = '\0';

		/****/ if (strcmp(str, "pi") == 0) {
			number = M_PI;
		} else if (strcmp(str, "e") == 0) {
			number = M_E;
		} else if (strcmp(str, "sin") == 0) {
			number = sin(process_function_body(s, out));
		} else if (strcmp(str, "cos") == 0) {
			number = cos(process_function_body(s, out));
		} else if (strcmp(str, "tan") == 0) {
			number = tan(process_function_body(s, out));
		} else if (strcmp(str, "asin") == 0 || strcmp(str, "arcsin") == 0) {
			number = asin(process_function_body(s, out));
		} else if (strcmp(str, "acos") == 0 || strcmp(str, "arccos") == 0) {
			number = acos(process_function_body(s, out));
		} else if (strcmp(str, "atan") == 0 || strcmp(str, "arctan") == 0) {
			number = atan(process_function_body(s, out));
		} else if (strcmp(str, "floor") == 0) {
			number = floor(process_function_body(s, out));
		} else if (strcmp(str, "ceil") == 0) {
			number = ceil(process_function_body(s, out));
		} else {
			*out = ERR_UNKNOWN; // ERROR: Function/Variable not found
			return 0;
		}

		if (*out != SUCCESS) {
			return 0;
		}

	} else {
		*out = ERR_UNKNOWN; // ERROR: Ecountered unknown symbol
		return 0;
	}

	return number * unary;
}

double process_function_body(char **s, CalcError *out)
{
	skip_whitespace(s);

	if (**s != '(') {
		*out = ERR_SYNTAX; // ERROR: Missing left function parenthese
		return 0;
	}

	(*s)++;

	double function_body = parse_expression(s, out);

	if (*out != SUCCESS) {
		return 0;
	}

	if (**s != ')') {
		*out = ERR_PAREN; // ERROR: Missing right function parenthese
		return 0;
	}

	(*s)++;

	return function_body;
}

double parse_power(char **s, CalcError *out)
{
	double base = parse_primary(s, out);

	if (*out != SUCCESS) {
		return 0;
	}

	double exponent = 0;

	skip_whitespace(s);

	if (**s == '^') {
		(*s)++;
		skip_whitespace(s);
		exponent = parse_power(s, out);

		if (*out != SUCCESS) {
			return 0;
		}
	} else {
		return base;
	}

	if (*out != 0) return 0;

	return pow(base, exponent);
}

double parse_term(char **s, CalcError *out)
{
	bool is_num = **s >= '0' && **s <= '9';

	double number = parse_power(s, out);
	if (*out != SUCCESS) {
		return 0;
	}

	skip_whitespace(s);

	while (**s == '*' || **s == '/' || **s == '(' 
			|| ((**s >= 'a' && **s <= 'z') || (**s <= 'A' && **s >= 'Z')) 
			|| (**s >= '0' && **s <= '9'))
	{
		if (**s == '*') {
			(*s)++;

			is_num = **s >= '0' && **s <= '9';

			number *= parse_power(s, out);

			if (*out != SUCCESS) {
				return 0;
			}
		}
		else if (**s == '/') {
			(*s)++;

			is_num = **s >= '0' && **s <= '9';

			double rhs = parse_power(s, out);

			if (*out != SUCCESS) {
				return 0;
			}

			if (rhs == 0) {
				*out = ERR_DIV_ZERO; // ERROR: Divide by zero
				return 0;
			}
			number /= rhs;
		}
		else if (**s == '(' || ((**s >= 'a' && **s <= 'z') || (**s <= 'A' && **s >= 'Z')) 
				|| (**s >= '0' && **s <= '9' && !is_num)) {

			is_num = **s >= '0' && **s <= '9';

			number *= parse_power(s, out);
			
			if (*out != SUCCESS) {
				return 0;
			}
		}
		else if (**s >= '0' && **s <= '9') {
			*out = ERR_SYNTAX;
			return 0;
		}

		if (*out != SUCCESS) {
			return 0;
		}

		skip_whitespace(s);
	}

	return number;
}

double parse_expression(char **s, CalcError *out)
{
	double number = parse_term(s, out);

	if (*out != SUCCESS) return 0;

	skip_whitespace(s);

	while (**s == '+' || **s == '-') {
		if (**s == '+') {
			(*s)++;
			number += parse_term(s, out);
			if (*out != SUCCESS) return 0;
		}
		else {
			(*s)++;
			number -= parse_term(s, out);
			if (*out != SUCCESS) return 0;
		}

		skip_whitespace(s);
	}

	return number;
}
