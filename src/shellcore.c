#include <assert.h>
#include <stdlib.h>

#include "debugger.h"
#include "libft.h"

#include "shellcore.h"
#include "env_singleton.h"
#include "env_access.h"
#include "prompt_singleton.h"
#include "executor.h"

t_shell	*_shell_create(char **env)
{
	t_shell	*shell;

	shell = ft_calloc(sizeof(t_shell), 1);
	if (shell)
	{
		shell->env = env_init(env);
		shell->lexer = lex_create();
		shell->parser = parser_create();
	}
	return (shell);
}

t_shell	*_shell_destroy(t_shell **shell)
{
	assert(shell);
	if (!shell)
		return (NULL);
	if (*shell)
	{
		env_deinit(&(*shell)->env);
		prompt_deinit(&(*shell)->prompt);
		lex_destroy(&(*shell)->lexer);
		parser_destroy(&(*shell)->parser);
		free(*shell);
		*shell = NULL;
	}
	return (NULL);
}

int	_shell_exec(t_shell *shell, const char *command_string)
{
	t_execscheme	*scheme;
	int				error;

	dbg("Executing command_string : '%s'\n", command_string);
	if (!lex(command_string))
	{
		dbg("Failed lexing command_string: '%s'\n", command_string);
		return (-1);
	}
	scheme = parse(preparser_get_next_area());
	if (!scheme)
	{
		dbg("Failed parsing command_string: '%s'\n", command_string);
		return (-1);
	}
	env_set_lasterror(0);
	while (scheme)
	{
		execscheme_pretty_dump(scheme, 15);
		error = execute(scheme);
		env_set_lasterror(error);
		scheme = parse(preparser_get_next_area());
	}
	return (error);
	(void)shell;
}

t_shellerr	_shell_loop(t_shell *shell)
{
	char	*line;
	int		last_error;

	shell->prompt = prompt_init();
	last_error = 0;
	while (1)
	{
		line = prompt(last_error);
		if (line == NULL)
			exit(0);
		last_error = _shell_exec(shell, line);
		free(line);
		if (_shell_was_interrupted())
			last_error = 130;
	}
	return (SHELL_ERRNO);
}
