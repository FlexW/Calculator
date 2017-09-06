/**
 * @file lexer.c
 * @brief Implementation of lexer functions.
 * @see lexer.h
 */
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"

#define NUM_STATES 5
#define STR_BUF_SIZE 100

typedef void (*state_handler)(char);

error_printer error_handler = NULL;

int state = 0;

char* input = NULL;
int input_col = 0;
int input_row = 0;
int input_len = 0;

bool lex_is_eof = false;

bool token_set = false;
token curr_token = 0;

int token_begin = 0;

char str_buf[STR_BUF_SIZE];

static void state0(char c);
static void state1(char c);
static void state2(char c);
static void state3(char c);
static void state4(char c);

static void token_found(token t);
static void error();

state_handler accept_in_state[5] = {state0,
                                    state1,
                                    state2,
                                    state3,
                                    state4};

static void set_str_buf(int start, int end) {
    int str_buf_index = 0;
    int i = start;
    for (; i <= end && str_buf_index < STR_BUF_SIZE - 1; i++, str_buf_index++) {
        str_buf[str_buf_index] = input[i];
    }
    str_buf[str_buf_index] = '\0';
}

static void unset_str_buf() {
    str_buf[0] = '\0';
}

static bool is_whitespace(char c) {
    return (c == ' ' ||
            c == '\n' ||
            c == '\r' ||
            c == '\t')
        ? true : false;
}

static bool is_operator(char c) {
    return (c == '+' ||
            c == '-' ||
            c == '*' ||
            c == '/' ||
            c == '^' ||
            c == '!' ||
            c == '(' ||
            c == ')' ||
            c == '|' ||
            c == '%')
    ? true : false;
}

static bool is_comma(char c) {
    return c == '.' ? true : false;
}

static bool is_digit(char c) {
    return (c >= '0' && c <= '9') ? true : false;
}

static bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') ? true : false;
}

static void error() {
    token_found(LEX_ERROR);
    set_str_buf(token_begin, input_col);
    input_col++;

    if (error_handler != NULL) {
        error_handler(lex_row_pos(),
                      lex_col_pos(),
                      "Illegal input: %s",
                      lex_get_str_buf());
    }
}

static void token_found(token t) {
    token_set = true;
    curr_token = t;
}

static void state0(char c) {
    unset_str_buf();
    token_begin = input_col;

    if (is_digit(c))
        state = 3;
    else if (is_letter(c))
        state = 2;
    else if (is_operator(c))
        state = 1;
    else if (is_whitespace(c))
        return;
    else
        error();
}

static token find_operator(char c) {
    switch (c) {
    case '+': return LEX_ADD;
    case '-': return LEX_SUB;
    case '*': return LEX_MUL;
    case '/': return LEX_DIV;
    case '^': return LEX_POW;
    case '%': return LEX_MOD;
    case '!': return LEX_FACT;
    case '(': return LEX_POPEN;
    case ')': return LEX_PCLOSE;
    case '|': return LEX_ABS;
    case '=': return LEX_ASSIGN;
    default: assert(0);
    }
}

static void state1(char c) {
    token_found(find_operator(input[input_col - 1]));
    unset_str_buf();
}

static void state2(char c) {
    if (!is_letter(c)) {
        token_found(LEX_ID);
        set_str_buf(token_begin, input_col - 1);
    }
}

static void state3(char c) {
    if (is_comma(c))
        state = 4;
    else if (!is_digit(c)) {
        token_found(LEX_NUM);
        set_str_buf(token_begin, input_col - 1);
    }
}

static void state4(char c) {
    if (is_digit(c))
        state = 3;
    else
        error();
}

void lex_init(char *str) {
    state = 0;
    input_col = 0;
    input = str;
    input_len = strlen(str);
    lex_is_eof = false;
}

token lex_next_token() {
    while (input_col < input_len) {
        accept_in_state[state](input[input_col]);
        if (token_set) {
            state = 0;
            token_set = false;
            return curr_token;
        }
        input_col++;
    }
    lex_is_eof = true;
    accept_in_state[state](0);
    return curr_token;
}

token lex_prev_token() {
    return curr_token;
}

bool lex_eoi() {
    return lex_is_eof;
}

char* lex_get_str_buf() {
    return str_buf;
}

int lex_col_pos() {
    return input_col;
}

int lex_row_pos() {
    return input_row;
}

void lex_set_error_printer(error_printer ep) {
    error_handler = ep;
}
