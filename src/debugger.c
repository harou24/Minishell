#include <assert.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ft_printf.h"

#include "debugger.h"

/*
** obvious problem here is that you cannot debug to STDIN, but why would you?
*/

static int			g_dbg_fd__;

static void			__debug_init()
{
	if (g_dbg_fd__ <= 0)
		debug_init_tofd(STDERR);
}

int					debug(const char *format, ...)
{
	va_list			args;
	int				rvalue;

	__debug_init();
	va_start(args, format);
	rvalue = ft_vdprintf(g_dbg_fd__, format, args);
	va_end(args);
	return (rvalue);
}

t_bool				debug_init_tofile(const char *filename)
{
	int				fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 0644);
	if (fd > 0)
	{
		g_dbg_fd__ = fd;
		return (TRUE);
	}
	return (FALSE);
}

t_bool				debug_init_tofd(int fd)
{
	if (fd > 0)
	{
		g_dbg_fd__ = fd;
		return (TRUE);
	}
	return (FALSE);
}

void				debug_deinit()
{
	if (g_dbg_fd__ > 0)
		close(g_dbg_fd__);
}
