/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debugger.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:09:05 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:09:06 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUGGER_H
# define DEBUGGER_H

# include <stdarg.h>

# include "libft.h"

# ifndef DEBUG
#  define DEBUG	0
# endif

# ifdef DEBUG_FILE
#  define DEBUG_TOFILE 1
# else
#  define DEBUG_TOFILE 0
#  define DEBUG_FILE ""
# endif

t_bool	debug_init_tofile(const char *filename);
t_bool	debug_init_tofd(int fd);
void	debug_deinit(void);
int		debug(const char *format, ...);

# define DBG_FILENAME_LEN 60
# define DBG_LINE_LEN 5
# define DBG_FUNCNAME_LEN 30

# define dbg(fmt, ...) \
        do { if (DEBUG) debug("%-*.*s%*d%*.*s(): " fmt, \
				DBG_FILENAME_LEN, DBG_FILENAME_LEN, __FILE__, \
				DBG_LINE_LEN, __LINE__, \
				DBG_FUNCNAME_LEN, DBG_FUNCNAME_LEN, __func__, \
				__VA_ARGS__); } while (0)
#endif
