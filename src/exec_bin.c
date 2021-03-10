#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "libft.h"
#include "debugger.h"

#include "bash_ops.h"
#include "path.h"

extern char **environ;

int		exec_bin(t_command *cmd)
{
	char	*_abspath;

	assert(cmd);
	_abspath = abspath(cmd->path);
	if (_abspath)
	{
		execve(_abspath, cmd->argv->argv, environ);

		/* execve only returns on error! */
		dbg("execve failed for %s with error : %s\n", _abspath, strerror(errno));
		return (-1);
	}
	/* command was not found, return appropriate error */
	return (-1);
}
