#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "debugger.h"
#include "bash_pattern.h"
#include "parser.h"
#include "env_singleton.h"

static size_t	g_begin;

void	preparser_reset(void)
{
	g_begin = 0;
}

t_range	preparser_get_next_area(void)
{
	t_token			*token;
	t_range			matchrange;

	matchrange = range(g_begin, g_begin);
	token = journal_get(matchrange.end);
	while (token)
	{
		if (token->type == SEMICOLON || token->type == NULLBYTE)
		{
			g_begin = matchrange.end + 1;
			return (matchrange);
		}
		matchrange.end++;
		token = journal_get(matchrange.end);
	}
	return (range(0, 0));
}
