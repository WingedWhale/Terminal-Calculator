#ifndef CALCULATOR
#define CALCULATOR

#include <stdbool.h>
#include <math.h>

double parse_number(const char **s, int *out);
double parse_primary(const char**s, int *out);
double parse_power(const char**s, int *out);
double parse_term(const char**s, int *out);
double parse_expression(const char**s, int *out);

#endif
