#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cmdargs.h"
#include "log.h"

typedef struct cmdarg cmdarg;
typedef struct table table;

struct table {
    int size;
    cmdarg** args;
};

/**
 * Structure for command line arguments.
 */
struct cmdarg {
    char* arg; /**< Command line argument. */
    char* value; /**< Value of Command line arg. Can be set with '='. */
};

table* ca_init(int num_of_args) {
    table *t = malloc(sizeof(*t));
    if (t == NULL) {
        perror("table malloc error: ");
        exit(1);
    }
    cmdarg **args = calloc(num_of_args, sizeof(cmdarg*));
    if (args == NULL) {
        perror("args calloc error: ");
        exit(1);
    }
    t->args = args;
    t->size = num_of_args;
    return t;
}

/**
 * Creates a new linked list node.
 * @param arg Argument.
 * @param tail Next node. If end NULL.
 * @returns arg_list.
 */
static cmdarg* new_cmdarg(char* arg, char* value) {
    cmdarg *l = malloc(sizeof(*l));
    if (l == NULL) {
        perror("new_cmdarg error: ");
        exit(1);
    }
    l->arg = arg;
    l->value = value;
    return l;
}

/**
 * Calculates a hash value from a string.
 * The index for a specific string will be equal to sum of ASCII values
 * of characters multiplied by their respective order in the string
 * after which it is modulo with table_size.
 * @param str String.
 * @param table_size Size of table where element gets saved.
 * @returns Index.
 */
static int hash(char* str, int table_size) {
    int sum = 0;
    int frequency[26] = {0};
    int slen = strlen(str);
    for (int i = 0; i < slen; i++) {
        frequency[(str[i] - 'a')]++;
    }
    for (int i = 0; i < 26; i++) {
            sum += (('a' + i) * frequency[i]);
    }
    int hash = (sum % table_size);
    LOG_DEBUG("hash value: %d", hash);
    return hash;
}

/**
 * Inserts a new element into the hash table.
 * @param element Element to insert.
 * @param t Table.
 */
static void insert(cmdarg* element, table* t) {
    LOG_DEBUG("insert key: %s, value: %s", element->arg, element->value);
    char* key = element->arg;
    int index = hash(key, t->size);
    cmdarg** start = t->args;
    while (*(start + index) != 0) {
      //LOG_DEBUG("%d", *(start+index));
        index = (index + 1) % t->size;
    }
    LOG_DEBUG("insert at index: %d", index);
    *(start + index) = element;
}

/**
 * Looks for a key in the hash table.
 * @param str Key to lookup.
 * @param t Table.
 * @returns Address of element. If not found NULL.
 */
static cmdarg* search(char* key, table* t) {
    int index = hash(key, t->size);
    cmdarg** start = t->args;
    while (*(start + index) != 0 && strcmp((*(start + index))->arg, key))
        index = (index + 1) % t->size;

    if(*(start + index) == 0)
        return NULL;
    return *(start + index);
}

/**
 * Searches for equal sign in string.
 * @param str String to search.
 * @returns Index of equal sign. If not found -1.
 */
static int eq_index(char* str) {
    LOG_DEBUG("string: %s", str);
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if(str[i] == '=') {
            LOG_DEBUG("equal sign found at %d", i);
            return i;
        }
    }
    LOG_DEBUG("equal sign not found");
    return -1;
}

void ca_parse_args(int argc, char* argv[], table* t) {
    LOG_DEBUG("argc: %d", argc);
    for (int i = 1; i < argc; i++) {
        int eqi = eq_index(argv[i]);
        cmdarg* element;
        if (eqi != -1) {
            LOG_DEBUG("Set %c sign to 0", argv[i][eqi]);
            argv[i][eqi] = '\0';
            LOG_DEBUG("key: %s, value: %s", argv[i], &argv[i][eqi + 1]);
            element = new_cmdarg(argv[i], &argv[i][eqi + 1]);
            insert(element, t);
            continue;
        }
        element = new_cmdarg(argv[i], NULL);
        insert(element, t);
    }
}

bool ca_is_arg(char* arg, table* t) {
    if (search(arg, t) != NULL)
        return true;
    return false;
}

char* ca_get_value(char *arg, table* t) {
    cmdarg *ca = search(arg, t);
    if (ca != NULL)
        return ca->value;
    return NULL;
}
