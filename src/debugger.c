#include <assert.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ft_printf.h"

#include "debugger.h"

int			g_dbg_fd__;

static void	__debug_init(void)
{
	if (g_dbg_fd__ <= 0)
	{
		if (DEBUG_TOFILE)
			debug_init_tofile(DEBUG_FILE);
		else
			debug_init_tofd(STDERR);
	}
}

void	debug_deinit(void)
{
	if (g_dbg_fd__ > 0)
	{
		close(g_dbg_fd__);
		g_dbg_fd__ = 0;
	}
}

int	debug(const char *format, ...)
{
	va_list			args;
	int				rvalue;

	__debug_init();
	va_start(args, format);
	rvalue = ft_vdprintf(g_dbg_fd__, format, args);
	va_end(args);
	return (rvalue);
}
