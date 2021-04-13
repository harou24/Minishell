#include <assert.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ft_printf.h"

#include "debugger.h"

extern int	g_dbg_fd__;

static void	__debug_print_banner(void)
{
	ft_dprintf(g_dbg_fd__, "%-*s%*s%*s%s\n\n",
		DBG_FILENAME_LEN, "Filename",
		DBG_LINE_LEN, "LINE",
		DBG_FUNCNAME_LEN + 3, "Function",
		" Output");
}

t_bool	debug_init_tofile(const char *filename)
{
	int				fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_APPEND | O_CREAT, 0644);
	if (fd > 0)
	{
		g_dbg_fd__ = fd;
		__debug_print_banner();
		return (TRUE);
	}
	return (FALSE);
}

t_bool	debug_init_tofd(int fd)
{
	if (fd > 0)
	{
		g_dbg_fd__ = fd;
		__debug_print_banner();
		return (TRUE);
	}
	return (FALSE);
}
