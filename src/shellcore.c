#include <assert.h>
#include <stdlib.h>

#include "debugger.h"
#include "libft.h"

#include "shellcore.h"
#include "env_access.h"

t_shell			*_shell_create(char **env)
{
	t_shell		*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (shell)
	{
		shell->env = env_create((const char **)env); /* update env functions ?*/
		shell->lexer = lex_create();
		shell->parser = parser_create();
	}
	return (shell);
}

t_shell		*_shell_destroy(t_shell **shell)
{
	assert(shell);
	if (!shell)
		return (NULL);
	if (*shell)
	{
		env_destroy((*shell)->env);
		lex_destroy(&(*shell)->lexer);
		parser_destroy(&(*shell)->parser);
		free(*shell);
		*shell = NULL;
	}
	return (NULL);
}

int			_shell_exec(t_shell *shell, const char *command_string)
{
	(void)shell;
	(void)command_string;
	return (-1);
}

t_shellerr	_shell_loop(t_shell *shell)
{
	/* shell->prompt = prompt_create(env_get_user(), env_get_host()); */
	while (1)
	{
	}
	prompt_destroy(shell->prompt);
	return (SHELL_ERRNO); /* stub */
}
