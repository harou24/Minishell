#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "libft.h"
#include "debugger.h"

#include "env_access.h"
#include "bash_ops.h"
#include "path.h"

extern char **environ;

int		exec_bin(t_command *cmd)
{
	char	*abspath;

	assert(cmd);
	abspath = path_expand(env_get_path(), cmd->path);
	if (abspath)
	{
		execve(abspath, cmd->argv->argv, environ);

		/* execve only returns on error! */
		dbg("execve failed for %s with error : %s\n", abspath, strerror(errno));
		return (-1);
	}
	/* command was not found, return appropriate error */
	exit(127);
}
