/**
 * @file errm.h
 * @brief Outputs error messages to the user.
 */

#ifndef ERRM_H_
#define ERRM_H_

/**
 * Prints out a error message to the user.
 * Prints line and column number.
 * @param row Row number.
 * @param col Column number.
 * @param fmt Format string.
 * @param ... Format string parameters.
 */
void errm_printf(int row, int col, char *fmt, ...);

#endif
