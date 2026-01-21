#ifndef CALCULATOR
#define CALCULATOR

#include <stdbool.h>
#include <math.h>

double parse_number(char **s, int *out);
double parse_primary(char**s, int *out);
double parse_power(char**s, int *out);
double parse_term(char**s, int *out);
double parse_expression(char**s, int *out);

#endif
