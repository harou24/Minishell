#ifndef DEBUGGER_H
# define DEBUGGER_H

#include <stdarg.h>

#include "libft.h"

#ifndef DEBUG
# define DEBUG 0
#endif

/* init functions return FALSE on error, handle errno at your discretion */

t_bool				debug_init_tofile(const char *filename);
t_bool				debug_init_tofd(int fd);
void				debug_deinit();
int					debug(const char *format, ...);

/* #define dbg(fmt, ...) do { if (DEBUG) { debug(__VA_ARGS__); } } while (0) */

/* https://stackoverflow.com/questions/1644868/define-macro-for-debug-printing-in-c */

#define dbg(fmt, ...) \
        do { if (DEBUG) debug("%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)


#endif
