#ifndef CALCULATOR
#define CALCULATOR

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
	SUCCESS = 0,
	ERR_DIV_ZERO = 1,
	ERR_SYNTAX = 2,
	ERR_PAREN = 3,
	ERR_UNKNOWN = 4
} CalcError;

double parse_number(char **s, CalcError *out);
double parse_primary(char**s, CalcError *out);
double process_function_body(char **s, CalcError *out);
double parse_power(char**s, CalcError *out);
double parse_term(char**s, CalcError *out);
double parse_expression(char**s, CalcError *out);

#endif
