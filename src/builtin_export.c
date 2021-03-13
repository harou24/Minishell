#include "bash_ops.h"
#include "env_singleton.h"
#include "env.h"
#include "pair.h"
#include <stdlib.h>

static	t_bool	__set(const char *to_be_splited)
{

	t_bool	ret;
	t_pair	*to_set;

	ret = TRUE;
	/*need split_line_into_key_value_pair()->env_singleton ??? */
	to_set = split_line_into_key_value_pair(to_be_splited);
	if (!to_set || env_set_s(to_set->f.key, to_set->s.value))
		ret = FALSE;
	pair_destroy(to_set);
	return (ret);
}

int		builtin_set(t_command *cmd)
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
