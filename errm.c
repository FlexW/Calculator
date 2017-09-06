#define _XOPEN_SOURCE
#define _ISOC99_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdarg.h>

#include "errm.h"

#define ERR_MSG_BUF_SIZE 100

static char err_msg_buf[ERR_MSG_BUF_SIZE];

void errm_printf(int row, int col, char *fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vsnprintf(err_msg_buf, ERR_MSG_BUF_SIZE, fmt, va);
    va_end(va);

    printf("%d:%d %s\n", row, col, err_msg_buf);
}
