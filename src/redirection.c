#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "debugger.h"
#include "filesystem.h"
#include "ft_unistd.h"

#include "libft.h"

static int	g_fd__[2];

void	redirection_std_push(void)
{
	g_fd__[STDIN] = dup(STDIN);
	g_fd__[STDOUT] = dup(STDOUT);
}

void	redirection_std_pop(void)
{
	dup2(g_fd__[STDIN], STDIN);
	dup2(g_fd__[STDOUT], STDOUT);
}

t_bool	redirection_stdout_to_pipe(const char *fname,
						t_bool should_append)
{
	int			fd;

	if (should_append)
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		dbg("Failing opening file{%s} for dupping to stdout, errno %s\n",
			fname, strerror(errno));
		return (FALSE);
	}
	if (dup2(fd, STDOUT) == -1)
	{
		dbg("Failing dupping to stdout, errno %s\n", strerror(errno));
		close(fd);
		return (FALSE);
	}
	close (fd);
	return (TRUE);
}

t_bool	redirection_file_to_stdin(const char *fname)
{
	int			fd;

	fd = fs_open(fname, O_RDONLY);
	if (fd == -1)
	{
		dbg("Failing opening file{%s} for dupping to stdin, errno %s\n",
			fname, strerror(errno));
		return (FALSE);
	}
	if (dup2(fd, STDIN) == -1)
	{
		dbg("Failing dupping stdin, errno %s\n", strerror(errno));
		close(fd);
		return (FALSE);
	}
	close(fd);
	return (TRUE);
}

t_bool	redirection_pipe_to_stdin(int pipe[2])
{
	if (dup2(pipe[PIPE_READ], STDIN) == -1)
	{
		dbg("Failing dupping stdin, errno %s\n", strerror(errno));
		return (FALSE);
	}
	drop_pipe(pipe);
	return (TRUE);
}
