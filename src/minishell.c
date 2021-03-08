#include <assert.h>
#include <stdlib.h>

#include "debugger.h"
#include "libft.h"

#include "minishell.h"
#include "shellcore.h"

extern char **environ;

static t_shell	*g_shell__;

t_shellerr		shell_interactive(char **env)
{
	t_shellerr	err;

	if (g_shell__)
		return (SHELL_EXISTS);
	err = shell_init(env);
	if (err == SHELL_OK)
		return (_shell_loop(g_shell__));
	else
		return (err);
}

t_shellerr		shell_init(char **env)
{
	if (g_shell__)
		return (SHELL_EXISTS);
	g_shell__ = _shell_create((env == NULL) ? environ : env);
	return (g_shell__ != NULL ? SHELL_OK : SHELL_ERRNO);
}

void	shell_deinit()
{
	if (g_shell__)
		_shell_destroy(&g_shell__);
}

int			shell_exec(const char *command_string)
{
	t_shell	*shell;
	int		rvalue;

	if (g_shell__)
	{
		/* use initialized singleton shell */
		return (_shell_exec(g_shell__, command_string));
	}
	else
	{
		/* setup shell on a single use basis */
		shell = _shell_create(environ);
		rvalue = _shell_exec(g_shell__, command_string);
		_shell_destroy(&shell);
		return (rvalue);
	}
}
