/**
 * @file cmdargs.h
 * @brief Parses command line options.
 *
 * Example Usage:
 * @code
 * ca_table* t = ca_init(NUMBER_OF_POSSIBLE_ARGS);
 * ca_parse_args(argc, argv, t);
 *
 * if (ca_is_arg("file", t)) {
 *     // Do something if option is set.
 * }
 * @endcode
 */

#ifndef CMDARGS_H_
#define CMDARGS_H_

#include <stdbool.h>

typedef struct ca_table ca_table;

/**
 * Initializes the parser.
 * This must be called before any other function.
 * @param num_of_args Number of command line options.
 * @returns Table to operate on.
 */
ca_table* ca_init(int num_of_args);

/**
 * Parses the given command line arguments.
 * After this function is called. One can check if a argument is
 * set with is_arg().
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @param t Table.
 */
void ca_parse_args(int argc, char* argv[], ca_table* t);

/**
 * Checks if the given argument is set.
 * Call this after called parse_args().
 * @param arg Argument.
 * @param t Table.
 * @returns True if is set. False if not.
 */
bool ca_is_arg(char* arg, ca_table* t);

/**
 * Gets the value for a Argument.
 * @param arg Argument.
 * @param t Table.
 * @returns Value if set. NULL if not set.
 */
char* ca_get_value(char* arg, ca_table* t);

#endif
