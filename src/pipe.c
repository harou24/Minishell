#include <assert.h>
#include <stdlib.h>

#include <unistd.h>

#include "debugger.h"
#include "libft.h"

#include "pipe.h"

/*
** ft_pipe() is a wrapper function for pipe syscall since for some reason
** 42 decided not to learn us standardized features. At some point we
** might have to hack around pipe() syscall just to pass this project..
*/

int		ft_pipe(int pipefd[2])
{
	return (pipe(pipefd));
}
