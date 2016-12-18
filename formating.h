#ifndef _FORMATING_H
#define _FORMATING_H

#include <stdbool.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#define ROUND_PLACES 3

void cut_zeros ( double d, char *c );
void fround ( double* d, int places );

#endif
