#include "bash_ops.h"
#include "env_singleton.h"
#include "env.h"
#include "pair.h"
#include <stdlib.h>

static	t_bool	__set(const char *to_be_set)
{
	t_bool	no_error_occured;
	t_pair	*to_set;

	no_error_occured = TRUE;
	to_set = split_line_into_key_value_pair(to_be_set);
	if (!to_set || !env_set_s(to_set->f.key, to_set->s.value))
		no_error_occured = FALSE;
	pair_destroy(to_set);
	return (no_error_occured);
}

int		builtin_export(t_command *cmd)
{	
	int	exit_status;
	int	count;

	if (cmd->argv->argc == 1)
	{
		/* print shell variables */
		exit_status = EXIT_SUCCESS;
	}
	else
	{
		count = 1;
		while (count < cmd->argv->argc)
		{
			if(!__set(cmd->argv->argv[count]))
				exit_status = EXIT_FAILURE;
			count++;
		}
	}
	exit(exit_status);
}
