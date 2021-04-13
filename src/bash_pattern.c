#include <stdlib.h>
#include "bash_pattern.h"

/*
** Bash Patterns
** matching works as follows:
**   - the matcher, bash_match_pattern(), takes a token vector as input
**   - it try to find a pattern for the whole length of the vector first
**   - if it cannot find a pattern, it will reduce it's match length by one
**     until a pattern is matched (or a P_NO_TYPE is returned)
**
** the patterns are specified in the g_pat_list[] global table:
**   - it has a fixed subpattern of token types which must always be found
**     at the begining of the token stream (fixed_types[])
**   - once it has matched such a pattern it matched as many 'fuzzy' types
**     types which may come in any order and any number (fuzzy_types[])
*/

static const t_bash_pattern	g_pat_list[] = {
	{P_COMMAND, 3, {WORD, SPACE, WORD}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 3, {WORD, SPACE, SYM}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 3, {SYM, SPACE, SYM}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 3, {SYM, SPACE, WORD}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 3, {SPACE, WORD, SPACE}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 3, {SPACE, SYM, SPACE}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 3, {SPACE, WORD, SYM}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 3, {SPACE, SYM, WORD}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 2, {WORD, SYM}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_COMMAND, 2, {SYM, WORD}, 4, {WORD, SYM, SPACE, ASSIGNMENT}},
	{P_PATH, 1, {WORD}, 2, {SYM, WORD}},
	{P_PATH, 1, {SYM}, 2, {SYM, WORD}},
	{P_PATH, 2, {WORD, SPACE}, 2, {SYM, WORD}},
	{P_PATH, 2, {SYM, SPACE}, 2, {SYM, WORD}},
	{P_PATH, 2, {SPACE, WORD}, 2, {SYM, WORD}},
	{P_PATH, 2, {SPACE, SYM}, 2, {SYM, WORD}},
	{P_ASSIGNMENT, 4, {SPACE, WORD, ASSIGNMENT, WORD}, 0, {}},
	{P_ASSIGNMENT, 3, {WORD, ASSIGNMENT, WORD}, 0, {}},
	{P_ASSIGNMENT, 3, {SPACE, WORD, ASSIGNMENT}, 0, {}},
	{P_ASSIGNMENT, 2, {WORD, ASSIGNMENT}, 0, {}}
						};

static t_bool	match_token_to_any_type(t_token *token,
				const t_token_type_e *types,
				size_t types_len)
{
	while (types_len > 0)
	{
		if (match_token_to_type(token, types[types_len - 1]))
			return (TRUE);
		types_len--;
	}
	return (FALSE);
}

static t_bool	match_fuzzy(t_range range, const t_token_type_e *fuzzy_types,
			size_t fuzzy_types_len)
{
	size_t	i;

	if (range.end >= journal_size())
		return (FALSE);
	i = 0;
	while (in_range(range, i))
	{
		if (!match_token_to_any_type(journal_get(range.begin + i),
				fuzzy_types, fuzzy_types_len))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	match_fixed(t_range range, const t_token_type_e *fixed_types,
			size_t fixed_types_len)
{
	size_t	i;

	if (range.end >= journal_size()
		|| range.end - range.begin + 1 < fixed_types_len)
		return (FALSE);
	i = 0;
	while (in_range(range, i) && i < fixed_types_len)
	{
		if (!match_token_to_type(journal_get(range.begin + i), fixed_types[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static t_bool	is_bash_pattern(t_range r, const t_bash_pattern *pattern)
{
	return (match_fixed(r, pattern->fixed_types, pattern->fixed_types_len)
		&& match_fuzzy(range(r.begin + pattern->fixed_types_len, r.end),
			pattern->fuzzy_types, pattern->fuzzy_types_len));
}

/*
** takes t_range and looks for t_bash_pattern_type with longest fixed size
** - t_range is expected to contain index of begin and end of the lexer/parser
**   tokens to match on
*/

t_bash_pattern_type	bash_match_pattern(t_range range)
{
	const size_t	g_pat_list_size = sizeof(g_pat_list)
						/ sizeof(g_pat_list[0]);
	t_bash_pattern	*candidate;
	size_t			i;

	candidate = NULL;
	i = 0;
	while (i < g_pat_list_size)
	{
		if (is_bash_pattern(range, &g_pat_list[i]))
		{
			if (candidate == NULL
				|| g_pat_list[i].fixed_types_len > candidate->fixed_types_len)
			{
				candidate = (t_bash_pattern *)&g_pat_list[i];
			}
		}
		i++;
	}
	if (candidate == NULL)
		return (P_NO_TYPE);
	else
		return (candidate->pattern_type);
}
