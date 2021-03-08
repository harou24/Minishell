#ifndef DEBUGGER_H
# define DEBUGGER_H

#include <stdarg.h>

#include "libft.h"

#ifndef DEBUG
# define DEBUG 0
#endif

#ifdef DEBUG_FILE
# define DEBUG_TOFILE 1
#else
# define DEBUG_TOFILE 0
#endif

/* init functions return FALSE on error, handle errno at your discretion */

t_bool				debug_init_tofile(const char *filename);
t_bool				debug_init_tofd(int fd);
void				debug_deinit();
int					debug(const char *format, ...);

#define DBG_FILENAME_LEN	50
#define DBG_LINE_LEN		5
#define DBG_FUNCNAME_LEN	25

/* https://stackoverflow.com/questions/1644868/define-macro-for-debug-printing-in-c */
#define dbg(fmt, ...) \
        do { if (DEBUG) debug("%-*s%*d%*s(): " fmt, \
				DBG_FILENAME_LEN, __FILE__, \
				DBG_LINE_LEN, __LINE__, \
				DBG_FUNCNAME_LEN, __func__, \
				__VA_ARGS__); } while (0)


#endif
