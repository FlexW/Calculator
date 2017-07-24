#include "calc.h"

char buffer[1024];
char output[30]; // TODO: Must be zeroed

void interactive_mode ( );

int main ( int argc, const char *argv[] ) {
  FILE *file;
  int j = 1;
  char *exp;
  
  if (argc < 2) {
    printf( "Please type at least one option.\n\n-h for help\n");
    exit( 0 );
  }

  for (int i = 1; i < argc; i++) {
    
    if (strcmp( "-h", argv[i] ) == 0  ||
        strcmp( "--help", argv[i] ) == 0 ) {
      // TODO: Implement help.
      printf( "Options:\n-i Starts interactive mode.\n\
-f filename Opens a textfile and evaluate all expressions.\n\
-d 4+4 Calculates the given expression.\n\n\
Calculator handels this operations:\n\
Pi        Pi number\n\
e         Euler's number\n\
sqrt()    Square root\n\
cos()     Cosine\n\
sin()     Sine\n\
tan()     Tangent\n\ 
lg()      Decimal logarithm\n\
ln()      Natural logarithm\n\
()        Brackets\n\
||        Absolute value\n\
!         Factorial\n\
-         Unary minus\n\
^         Exponent\n\
mod()     Modulus divide\n\ 
*, /      Multiply, Divide\n\
+, -      Add, Subtract\n" );
      exit( 0);
    }

    // File
    else if (strcmp( "-f", argv[i] ) == 0 ||
             strcmp( "--file", argv[i] ) == 0) {
      file = fopen ( argv[i + 1], "r" );

      while ( fgets ( buffer, 1024, file ) ) {

        calculate( buffer, output );
        printf( "%i >> %s\n", j, output );
        j++;
      }
    }

    // Direct mode
    else if (strcmp( "-d", argv[i] ) == 0 ||
             strcmp( "--direct", argv[i] ) == 0) {

      calculate( argv[i + 1], output );
      printf( ">> %s\n", output );

      exit( 0 );
    }

    //Interactive mode
    else if (strcmp( "-i", argv[i] ) == 0 ||
             strcmp( "--interactive", argv[i] ) == 0) {
      interactive_mode( );
    }
    else
      // TODO: Error handling
      ;
  }

  return 0;
}

void interactive_mode ( ) {
  
  while (true) {
    printf( "<< " );
    if (NULL == fgets( buffer, 1024, stdin ))
      // TODO: Impliment error handling
      ;
    calculate( buffer, output );
    printf( ">> %s\n", output );
  }
}
