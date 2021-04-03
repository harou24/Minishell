#include <stdlib.h>

#include <unistd.h>

#include "debugger.h"
#include "libft.h"

/*
** ft_pipe() is a wrapper function for the pipe syscall since for some reason
** 42 sometimes mistakes a requirement for a nice to have. At some point we
** might have to hack around pipe() to pass this project.
*/

int	ft_pipe(int pipefd[2])
{
	return (pipe(pipefd));
}
