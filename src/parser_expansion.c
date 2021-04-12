#include <assert.h>

#include "debugger.h"
#include "env_singleton.h"
#include "parser.h"

extern t_parser	*g_parser__;

t_bool	parse_should_expand_literals(void)
{
	t_token		*string;
	t_token		*literal;

	string = journal_find_nth_type(STRING, 0);
	literal = journal_find_nth_type(LITERAL, 0);
	return (!string || (string && literal && string->index > literal->index));
}

t_bool	parse_expand(void)
{
	size_t	jsize;

	jsize = journal_size();
	if (parse_should_expand_literals())
	{
		if (!parse_expand_strings(LITERAL))
			return (FALSE);
	}
	if (!parse_expand_variables())
		return (FALSE);
	if (!parse_expand_strings(STRING))
		return (FALSE);
	g_parser__->matcharea.end -= jsize - journal_size();
	return (TRUE);
}
