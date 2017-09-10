#ifndef _CALC_H
#define _CALC_H

#define E "2.71828182846"

#define PI "3.14159265359"

#define calc_rad(x) x * 0.017453292519943295

enum token_type {
  NEW = 0,
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
  ABS_VAL = 11,
  //ABS_VAL_OPEN = 11,
  //ABS_VAL_CLOSE = 12,
  SQRT = 13,
  COS = 14,
  SIN = 15,
  TAN = 16,
  LG = 17,
  LN = 18,
  UNMIN = 19,
  CONS = 20,
  NONE = 21
};

typedef struct {
  int token;
  char* value;
} TOKEN;

void calculate(const char* exp, char* output, int output_size);

#endif
