/**
 * @file log.h
 * Logging utility.
 * To print to stdout, just use the macro LOG_INFO or LOG_DEBUG.
 * INFO or DEBUG tag, file name, line number and current function
 * will be always printed.
 * <br>
 * To activate logging pass -DLOGDEBUG or/and -DLOGINFO to the compiler.
 * Alternatively #define LOGDEBUG or/and LOGINFO.
 * <br>
 * Usage:
 * LOG_INFO("This is %d logging statement.", 1);
 * <br>
 * Output:
 * [INFO] file.c:205: sample_func(): This is 1 logging statement.
 * <br>
 * To print to a file, set the file using:
 * set_logging_file(fname);
 */

#ifndef LOG_H_
#define LOG_H_

#define _XOPEN_SOURCE
#define _ISOC99_SOURCE
#define _BSD_SOURCE

#if (__STDC_VERSION__ < 199901L)
#error "C99 Compiler for logging needed."
#endif

#include <stdarg.h>
#include <stdio.h>

#define PR_BUFFER_SIZE 100

char pr_buffer[PR_BUFFER_SIZE];
FILE** log_file = &stdout;

/**
 * Sets the logging file.
 * The file will be created if it not exists.
 * If the file exist, it will be erased.
 * @param fname Filename.
 */
void set_logging_file(char* fname) {
    FILE *f = fopen(fname, "w");
    if (f == NULL)
        return;
    log_file = &f;
}

void dlog(const char* tag, const char* fname, int linnum, const char* fxname,
          char* fmt, ...) {
    va_list va;
    va_start(va, fmt);
    vsnprintf(pr_buffer, PR_BUFFER_SIZE, fmt, va);
    va_end(va);
    fprintf(*log_file, "[%s] %s:%d %s(): %s\n", tag, fname, linnum, fxname, pr_buffer);
}

#ifdef LOGINFO
#define LOG_INFO(fmt, ...)                                              \
    dlog("INFO", __FILE__, __LINE__, __func__, (fmt), ##__VA_ARGS__);
#else
#define LOG_INFO(fmt, ...) do {} while (0)
#endif

#ifdef LOGDEBUG
#define LOG_DEBUG(fmt, ...)                                             \
    dlog("DEBUG", __FILE__, __LINE__, __func__, (fmt), ##__VA_ARGS__);
#else
#define LOG_DEBUG(fmt, ...) do {} while (0)
#endif

#endif /* LOG_H_ */
