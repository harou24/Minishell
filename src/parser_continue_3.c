#include <assert.h>

#include "debugger.h"
#include "parser.h"

extern t_parser	*g_parser__;

t_bool	parse_keep_matching(void)
{
	return (g_parser__->matcharea.begin < g_parser__->matcharea.end);
}

char	*parse_build_path(t_range *area)
{
	if (journal_at_index_is_type(area->begin, SPACE))
	{
		area->begin += 1;
		return (journal_get_string_for_index(area->begin));
	}
	else
	{
		return (journal_get_string_for_index(area->begin));
	}
}

char	*parse_build_argument(size_t *index, int *len)
{
	t_token		*token;
	char		*arg;

	token = journal_get(*index);
	arg = NULL;
	while (token && token->type != SPACE && token->type != NULLBYTE && *len > 0)
	{
		arg = ft_strjoin_noreuse(arg, journal_get_string_for_index(*index));
		(*len)--;
		(*index)++;
		token = journal_get(*index);
	}
	return (arg);
}

t_argv	*parse_build_argv(t_range area)
{
	char		*arg;
	int			len;
	t_argv		*argv;

	len = range_len(area);
	argv = argv_create(len);
	if (argv)
	{
		while (len > 0)
		{
			arg = parse_build_argument(&area.begin, &len);
			if (arg)
				argv_push(argv, arg);
			area.begin++;
			len--;
		}
	}
	return (argv);
}

t_command	*parse_build_command(t_range area)
{
	char		*path;
	t_argv		*argv;
	t_command	*command;

	path = parse_build_path(&area);
	argv = parse_build_argv(area);
	command = command_create(path, argv);
	return (command);
}
