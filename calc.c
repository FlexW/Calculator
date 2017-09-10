/*
    Pi        Pi number
    e         Euler's number
    sqrt()    Square root
    cos()     Cosine (using radians as an argument)
    sin()     Sine (using radians as an argument)
    tan()     Tangent (using radians as an argument)
    lg()      Decimal logarithm
    ln()      Natural logarithm
1   ()        Brackets
2   ||        Absolute value, e.g. |-5 - 10|
3   !         Factorial
4   -         Unary minus
5   ^         Exponent
6   mod       Modulus divide (only integer)
7   *, /      Multiply, Divide (left-to-right precedence)
8   +, -      Add, Subtract (left-to-right precedence)

Grammatic:

expression = component [ { + | -  component } ]
component = mod [ { * | / mod } ]
mod = pow [ { mod pow } ]
pow = unmin [ { ^ unmin } ]
unmin = facto | { - facto }
facto = absval | { absval [ ! ] }
absval = factor | | expression |
factor = number | ( expression ) | func
number = { 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | e | Pi }
func = sqrt | cos | sin | tan | lg | ln

*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#include "calc.h"
#include "formating.h"

static const char* input = NULL;
static bool get_pre_token = false;
static bool reset_lexer = true;

static double expression();
static double component();
static double mod();
static double power();
static double unmin();
static double facto();
static double abs_val();
static double factor();
static double number();

// This method is the lexer, it returns the next token.
static bool get_next_token(TOKEN *t) {
  static int curr_index = 0;
  static TOKEN pre_t;
  static bool abs_val_open = true;
  int i = 0;
  int j = 0;
  char *num;
  int len;

  if (pre_t.token == NONE) {
    t->token = NONE;
    return false;
  }

  // reset token
  t->token = NONE;

  // before something calculated --> reset
  if (reset_lexer) {
    pre_t.token = NEW;
    curr_index = 0;
    abs_val_open = true;
    get_pre_token = false;
    reset_lexer = false;
  }
  // If set, we do not want the next token,
  // we want the last token. In some cases this
  // must happen.
  if (get_pre_token) {
    t->token = pre_t.token;
    t->value = pre_t.value;
    get_pre_token = false;
    return true;
  }

  // Check if string is on the end.
  if (*(input + curr_index) == '\0') {
    pre_t.token = NONE;
    //curr_index = 0;
    //abs_val_open = true;
    return false;
  }

  // Check what the next symbol is
  while (t->token == NONE) {
    switch (*(input + curr_index)) {

    case '+':
      t->token = ADD;
      break;

    case '-':
      // Unary minus handling
      if (curr_index == 0)
	t->token = UNMIN;
      else if (pre_t.token != NUM)
	t->token = UNMIN;
      else
	t->token = SUB;
      break;

    case '*':
      t->token = MUL;
      break;

    case '/':
      t->token = DIV;
      break;

    case '(':
      t->token = PAR_OPEN;
      break;

    case ')':
      t->token = PAR_CLOSE;
      break;

    case '!':
      t->token = FACTORIAL;
      break;

    case '|':
/*
      if (abs_val_open) {
        t->token = ABS_VAL_OPEN;
        abs_val_open = false;
      }
      else {
        t->token = ABS_VAL_CLOSE;
        abs_val_open = true;
      }
*/
      t->token = ABS_VAL;
      break;

    case '^':
      t->token = POW;
      break;

    case 'e':
      t->token = CONS;
      t->value = E;
      break;

    case 'P':
      // Check if it is really Pi
      if (*(input + curr_index + 1) == 'i') {
        t->token = CONS;
        t->value = PI;
      }
      else {
        printf("Illegal input.\n");
        exit(1);
      }
      break;

    default:
      // Check if it is a number
      if (*(input + curr_index) >= 48 && *(input + curr_index) <= 57) {
        t->token = NUM;
      }
      // Check if it is a function
      else if ( *(input + curr_index) == 's' ||
        *(input + curr_index) == 'c' ||
        *(input + curr_index) == 't' ||
        *(input + curr_index) == 'l') {

        curr_index++;
        // sin
        if (*(input + curr_index) == 'i') {
          curr_index++;
          if (*(input + curr_index) != 'n') {
            printf("Illegal input.\n");
            exit(1);
          }
	  else {
	    t->token = SIN;
	  }
	}
	// cos
	else if (*(input + curr_index) == 'o') {
	  if (*(input + curr_index - 1) != 'c') {
	    printf("Illegal input.\n");
	    exit(1);
	  }
	  curr_index++;
	  if (*(input + curr_index) != 's') {
	    printf("Illegal input.\n");
	    exit(1);
	  }
	  else {
	    t->token = COS;
	  }
	}
	// tan
	else if (*(input + curr_index) == 'a') {
	  if (*(input + curr_index - 1) != 't') {
	    printf("Illegal input.\n");
	    exit(1);
	  }
	  curr_index++;
	  if (*(input + curr_index) != 'n') {
	    printf("Illegal input.\n");
	    exit(1);
	  }
	  else {
	    t->token = TAN;
	  }
	}
	// lg
	else if ( *(input + curr_index) == 'g' ) {
	  if (*(input + curr_index - 1) != 'l') {
	    printf("Illegal input.\n");
	    exit(1);
	  }
	  t->token = LG;
	}
	// ln
	else if (*(input + curr_index) == 'n') {
	  if (*(input + curr_index - 1) != 'l') {
	    printf("Illegal input.\n");
	    exit(1);
	  }
	  t->token = LN;
	}
	// sqrt
	else if (*(input + curr_index) == 'q') {
	  if (*(input + curr_index - 1) != 's') {
	    printf("Illegal input.\n");
	    exit(1);
	  }
	  curr_index = curr_index + 2;
	  if (*(input + curr_index) != 't') {
	    printf("Illegal input.\n");
	    exit(1);
	  }
	  else {
	    t->token = SQRT;
	  }
	}
	else {
	  printf("Illegal input.\n");
	  exit(1);
	}
      }
      else {
	// Check if string is at the end
	if (*(input + curr_index) == '\0') {
	  //curr_index = 0;
	  //abs_val_open = true;
	  t->token = NONE;
	  return false;
	}

	// If not then we have a space, tab or something else
	// increase index and then go again through the loop
       else if (*(input + curr_index) != ' ' &&
		*(input + curr_index) != '\t' &&
		*(input + curr_index) != '\r' &&
		*(input + curr_index) != '\n') {
	 printf("Illegal input.\n");
	 exit(1);
       }
	curr_index++;
      }
      break;
    }
  }


  // If we have found a number, then...
  if (t->token == NUM) {

    // Check how long the Number is
    i = curr_index;
    while (*(input + i) >= 48 && *(input + i) <= 57 ||
        *(input + i) == '.') {
      i++;
    }
    len = i - curr_index;

    // Now we can malloc memory
    num = (char*)malloc(sizeof(char) * len);
    if (num == NULL) {
      perror("malloc");
      exit(1);
    }

    // Copy number in the new memory
    while (curr_index < i) {
      *(num + j) = *(input + curr_index);
      j++;
      curr_index++;
    }

    // And then save it to the struct
    t->value = num;
  }
  else {
    curr_index++;
  }

  // If we have a constante then we need to change the token to NUM
  if (t->token == CONS)
    t->token = NUM;

  // Save token and value in the pre token struct, to acess it
  // if we need it
  pre_t.token = t->token;
  pre_t.value = t->value;

  return true;
}

// When this method is called, the get_nex_token
// method returns the last token
static void revert_token() {
  get_pre_token = true;
}

static double number() {
  TOKEN t;
  get_next_token(&t);
  if (t.token != NUM) {
    printf("Number expected.\n");
    exit(1);
  }
  return atof(t.value);
}

static double factor() {
  double comp;
  double num1;
  double num2;
  bool has_value = false;
  TOKEN t;

  // Get number
  num1 = mod();

  // Get next token
  get_next_token(&t);

  // Search for * or /
  while (t.token == MUL || t.token == DIV) {
    // Get second number
    num2 = mod();

    if (t.token == MUL) {
      comp = num1 * num2;
      num1 = comp;
    }
    else {
      comp = num1 / num2;
      num1 = comp;
    }

    // Flag to see if the comp value is filled,
    // it's important for later
    has_value = true;
    // Get the next token
    get_next_token(&t);
  }

  // If comp is empty then write just the first number in it
  if (!has_value)
    comp = num1;

  // Go one token back, because we call it in the loop one time to
  // often. So the next call of get_next_token, will return the
  // right token
  revert_token();
  return comp;
}

static double mod() {
  double mod;
  double power1;
  double power2;
  bool has_value = false;
  TOKEN t;

  power1 = power();
  get_next_token(&t);

  while (t.token == MOD) {
    power2 = power();

    mod = (int)power1 % (int)power2;
    power1 = mod;

    has_value = true;
    get_next_token(&t);
  }

  if (!has_value)
    mod = power1;

  revert_token();
  return mod;
}

static double power() {
  double power;
  double unmin1;
  double unmin2;
  bool has_value = false;
  TOKEN t;

  unmin1 = unmin();
  get_next_token(&t);

  while (t.token == POW) {
    unmin2 = unmin();
    power = pow(unmin1, unmin2);
    unmin1 = power;

    has_value = true;
    get_next_token(&t);
  }

  if (!has_value)
    power = unmin1;

  revert_token();
  return power;
}

static double unmin() {
  double unmin;
  double facto1;
  bool has_value = false;
  TOKEN t;

  get_next_token(&t);

  while (t.token == UNMIN) {
    facto1 = facto();
    unmin = -1.0 * facto1;

    has_value = true;
    get_next_token(&t);
  }

  revert_token();

  if (!has_value)
    unmin = facto();

  return unmin;
}

static double facto ( ) {
  double facto;
  double abs_val1;
  bool has_value = false;
  TOKEN t;

  abs_val1 = abs_val();
  get_next_token(&t);

  while (t.token == FACTORIAL) {
    facto = 1.0;

    for (int i = 1; i <= abs_val1; i++)
      facto *= i;

    abs_val1 = facto;

    has_value = true;
    get_next_token(&t);
  }

  if (!has_value)
    facto = abs_val1;

  revert_token();
  return facto;
}

static double abs_val ( ) {
  double abs_val;
  double comp;
  TOKEN t;

  get_next_token(&t);

  if (t.token == ABS_VAL) {
    // If there is an opening absolute value,
    // we have to start from the beginning
    comp = expression();

    get_next_token(&t);

    if (t.token != ABS_VAL) {
      printf("Expected abs val sign.\n");
      exit(1);
    }

    if (comp < 0)
      abs_val = -1 * comp;
    else
      abs_val = comp;
  }
  else {
    revert_token( );
    abs_val = component( );
  }

  return abs_val;
}

static double component() {
  double comp;
  TOKEN t;

  get_next_token(&t);

  // Switch trough all functions
  switch (t.token) {

  // sin
  case SIN:
    get_next_token(&t);
    if (t.token != PAR_OPEN) {
      printf("Expected par open.\n");
      exit(1);
    }
    comp = expression();
    get_next_token(&t);
    if (t.token != PAR_CLOSE) {
      printf("Expected par close.\n");
      exit(1);
    }
    // Calculate sinus, but first convert from degree to radiant
    comp = sin(calc_rad(comp));
    break;

  // cos
  case COS:
    get_next_token(&t);
    if (t.token != PAR_OPEN) {
      printf("Expected par open.\n");
      exit(1);
    }
    comp = expression();
    get_next_token(&t);
    if (t.token != PAR_CLOSE) {
      printf("Expected par close.\n");
      exit(1);
    }
    comp = cos(calc_rad(comp));
    break;

  // tan
  case TAN:
    get_next_token(&t);
    if (t.token != PAR_OPEN) {
      printf("Expected par open.\n");
      exit(1);
    }
    comp = expression();
    get_next_token(&t);
    if (t.token != PAR_CLOSE) {
      printf("Expected par close.\n");
      exit(1);
    }
    comp = tan(calc_rad(comp));
    break;

  //sqrt
  case SQRT:
    get_next_token(&t);
    if (t.token != PAR_OPEN) {
      printf("Expected par open.\n");
      exit(1);
    }
    comp = expression();
    get_next_token(&t);
    if (t.token != PAR_CLOSE) {
      printf("Expected par close.\n");
      exit(1);
    }
    comp = sqrt(comp);
    break;

  //ln
  case LN:
    get_next_token(&t);
    if (t.token != PAR_OPEN) {
      printf("Expected par open.\n");
      exit(1);
    }
    comp = expression();
    get_next_token(&t);
    if (t.token != PAR_CLOSE) {
      printf("Expected par close.\n");
      exit(1);
    }
    comp = log(comp);
    break;

  //log
  case LG:
    get_next_token(&t);
    if (t.token != PAR_OPEN) {
      printf("Expected par open.\n");
      exit(1);
    }
    comp = expression();
    get_next_token(&t);
    if (t.token != PAR_CLOSE) {
      printf("Expected par close.\n");
      exit(1);
    }
    comp = log10(comp);
    break;

  //par_open
  case PAR_OPEN:
    // Start again because a expression in parantheses
    // is like its own expression
    comp = expression();
    get_next_token(&t);

    if (t.token != PAR_CLOSE) {
      printf("Expected par close.\n");
      exit(1);
    }
    break;

  default:
    // If we go into here then we have a number.
    // reset token that number() picks the right one
    revert_token();
    comp = number();
    break;
  }

  return comp;
}

static double expression() {
  double exp;
  double factor1;
  double factor2;
  bool has_value = false;
  TOKEN t;

  factor1 = factor();
  get_next_token(&t);

  while (t.token == ADD || t.token == SUB) {
    factor2 = factor();

    if (t.token == ADD) {
      exp = factor1 + factor2;
      factor1 = exp;
    }
    else {
      exp = factor1 - factor2;
      factor1 = exp;
    }

    has_value = true;
    get_next_token(&t);
  }

  if (!has_value)
    exp = factor1;

  revert_token();
  return exp;
}

double parse(const char* exp) {
  double result;
  TOKEN t;
  // reset
  reset_lexer = true;
  // Write expression in global variable
  input = exp;
  // Parse expression
  result = expression();
  get_next_token(&t);

  //if (t.token != NONE) {
  //  printf("Unknown token\n");
  //  exit(1);
  //}

  return result;
}

 void calculate(const char* exp, char* output, int output_size) {
  double result;

  result = parse(exp);
  fround(&result, ROUND_PLACES);
  // We take the global input variable to return the result,
  // because no one uses the input variable anymore
  cut_zeros(result, output);
}
