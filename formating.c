#include "formating.h"
#include <stdio.h>

void cut_zeros ( double d, char* c ) {
  int len;
  int i;
  int places_before_pt = 0;
  bool is_float = false;
  
  if (1 != sprintf( c, "%f", d ))
    // TODO: Error handling
    ;

  len = strlen( c );

  // Check if we have a floating point number
  for (i = 0; i < len; i++) {
    places_before_pt++;
    if (*(c+i) == '.') {
      is_float = true;
      break;
    }
  }

  // If we have a float, we can cut the zeros
  if (is_float) {
    i = len - 1;
    while (true) {

      if (*(c+i) == '0')
	*(c+i) = '\0';

      else if (*(c+i) == '.') {
	*(c+i) = '\0';
	break;
      }
      else if (i < places_before_pt + ROUND_PLACES + 1)
	break;
      
      i--;
    }
  }
}

void fround ( double* d, int places ) {
  double p = pow( 10, places );
  *d = round( *d * p ) / p; 
}
