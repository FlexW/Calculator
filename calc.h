#ifndef _CALC_H
#define _CALC_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#define E "2.71828182846"

#define PI "3.14159265359"

#define calc_rad( x ) x * 0.017453292519943295

#define HELPTEXT "This is the help. Not implimented yet."

enum token_type {
  NONE = 0,
  NUM = 1,
  ADD = 2,
  MUL = 3,
  SUB = 4,
  DIV = 5,
  PAR_OPEN = 6,
  PAR_CLOSE = 7,
  POW = 8,
  FACTORIAL = 9,
  MOD = 10,
  ABS_VAL_OPEN = 11,
  ABS_VAL_CLOSE = 12,
  SQRT = 13,
  COS = 14,
  SIN = 15,
  TAN = 16,
  LG = 17,
  LN = 18,
  UNMIN = 19,
  CONS = 20
};

typedef struct {
  int token;
  char *value;
}TOKEN;

bool get_next_token ( TOKEN *t );

void revert_token ( );

double parse ( const char* exp );

double expression ( );

double factor ( );

double number ( );

double abs_val ( );

double facto ( );

double unmin ( );

double power ( );

double mod ( );

double component ( );

void calculate( char* exp, char* output );

#endif
