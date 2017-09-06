/**
 * @file lexer.h
 * @brief This is the lexer for the calculator.
 *
 * Example Usage:
 * @code
 * lex_init("(3 + 4) * 2 + x");
 *
 * while (!lex_eoi()) {
 *      token t = lex_next_token();
 *      if (t == LEX_ID)
 *         printf("ID:%s ", lex_get_str_buf());
 *     else if (t == LEX_NUM)
 *         printf("NUM:%s ", lex_get_str_buf());
 * }
 * @endcode
 * Output:
 * <br>
 * <code>NUM:3 NUM:4 NUM:2 ID:x</code>
 */
#ifndef LEXER_H_
#define LEXER_H_

#include <stdbool.h>

typedef void (*error_printer)(int row, int col, char* fmt, ...);

typedef enum token token;

enum token {
    LEX_ADD,
    LEX_SUB,
    LEX_DIV,
    LEX_MUL,
    LEX_POW,
    LEX_MOD,
    LEX_FACT,
    LEX_POPEN,
    LEX_PCLOSE,
    LEX_ABS,
    LEX_ASSIGN,
    LEX_ID,
    LEX_NUM,
    LEX_ERROR
};

/**
 * Initializes the lexer.
 * Call this function before any call to lex_next_token().
 * @param str Input string to lex.
 */
void lex_init(char *str);

/**
 * Returns the next token.
 * @returns Token.
 */
token lex_next_token();

/**
 * Returns previous token.
 * @returns Token.
 */
token lex_prev_token();

/**
 * Indicates if end of input is reached.
 * @returns True if end is reached. False if not.
 */
bool lex_eoi();

/**
 * If returned token from lex_next_token() has additional
 * content, it can be taken from here.
 * @returns Additional content.
 */
char* lex_get_str_buf();

/**
 * Get the lexer current position in the input.
 * @returns Input column position.
 */
int lex_col_pos();

/**
 * Get the lexer current position in the input.
 * @returns Input row position.
 */
int lex_row_pos();

/**
 * If error messages are wanted, set a handler with this
 * function.
 * Error messages will e printed with row and column information.
 * @param ep Error message printing handler.
 */
void lex_set_error_printer(error_printer ep);

#endif
