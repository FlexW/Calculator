#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "errm.h"

int main(int argc, char *argv[]) {
        token t;
        lex_init("3 + 4,++--09/*!^a%bc-a,aa");
        lex_set_error_printer(&errm_printf);
        while (!lex_eoi()) {
                t = lex_next_token();
                switch (t) {
                case LEX_ADD:
                        printf("+");
                        break;
                case LEX_SUB:
                        printf("-");
                        break;
                case LEX_DIV:
                        printf("/");
                        break;
                case LEX_MUL:
                        printf("*");
                        break;
                case LEX_FACT:
                        printf("!");
                        break;
                case LEX_POW:
                        printf("^");
                        break;
                case LEX_ABS:
                        printf("|");
                        break;
                case LEX_MOD:
                        printf("%%");
                        break;
                case LEX_ASSIGN:
                        printf("=");
                        break;
                case LEX_POPEN:
                        printf("(");
                        break;
                case LEX_PCLOSE:
                        printf(")");
                        break;
                case LEX_NUM:
                        printf("NUM: %s", lex_get_str_buf());
                        break;
                case LEX_ID:
                        printf("ID: %s", lex_get_str_buf());
                        break;
                }
                printf("\n");
        }
        return 0;
}
