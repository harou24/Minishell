#include <stdlib.h>
#include <assert.h>
#include "bash_pattern.h"

/*
** Bash Patterns
** matching works as follows:
**   - the matcher, bash_match_pattern(), takes a token vector as input
**   - it try to find a pattern for the whole length of the vector first
**   - if it cannot find a pattern, it will reduce it's match length by one
**     until a pattern is matched (or a P_NO_TYPE is returned)
**
** the patterns are specified in the pat_list[] global table:
**   - it has a fixed subpattern of token types which must always be found
**     at the begining of the token stream (fixed_types[])
**   - once it has matched such a pattern it matched as many 'fuzzy' types
**     types which may come in any order and any number (fuzzy_types[])
*/

static const t_bash_pattern pat_list[] =	{
												{ P_COMMAND, 3, {WORD, SPACE, WORD}, 3, {WORD, SPACE, ASSIGNMENT} },
												{ P_COMMAND, 4, {SPACE, WORD, SPACE, WORD}, 3, {WORD, SPACE, ASSIGNMENT} },
												{ P_PATH, 1, {WORD}, 0, {} },
												{ P_PATH, 2, {WORD, SPACE}, 0, {} },
												{ P_PATH, 2, {SPACE, WORD}, 0, {} },
												{ P_PATH, 3, {SPACE, WORD, SPACE}, 0, {} },
												{ P_ASSIGNMENT, 4, {SPACE, WORD, ASSIGNMENT, WORD}, 0, {} },
												{ P_ASSIGNMENT, 3, {WORD, ASSIGNMENT, WORD}, 0, {} },
												{ P_ASSIGNMENT, 3, {SPACE, WORD, ASSIGNMENT}, 0, {} },
												{ P_ASSIGNMENT, 2, {WORD, ASSIGNMENT}, 0, {} }
											};

t_bool					match_token_to_type(t_token *token, const e_token_type type)
{
	assert(token);
	return (token->type == type);
}

t_bool					match_token_to_any_type(t_token *token, const e_token_type *types, size_t types_len)
{
	assert(token);
	while(types_len > 0)
	{
		if (match_token_to_type(token, types[types_len - 1]))
			return (TRUE);
		types_len--;
	}
	return (FALSE);
}

t_bool					match_fuzzy(t_range range, const e_token_type *fuzzy_types, size_t fuzzy_types_len)
{
	size_t				i;

	if (range.end >= journal_size())
		return (FALSE);
	i = 0;
	while (in_range(range, i))
	{
		if (!match_token_to_any_type(journal_get(range.begin + i), fuzzy_types, fuzzy_types_len))
			return (FALSE);
		i++;	
	}
	return (TRUE);
}

t_bool					match_fixed(t_range range, const e_token_type *fixed_types, size_t fixed_types_len)
{
	size_t				i;

	if (range.end >= journal_size() || range.end - range.begin + 1 < fixed_types_len)
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

t_bool					is_bash_pattern(t_range r, const t_bash_pattern *pattern)
{
	return (match_fixed(r, pattern->fixed_types, pattern->fixed_types_len)
		&& match_fuzzy(range(r.begin + pattern->fixed_types_len, r.end), pattern->fuzzy_types, pattern->fuzzy_types_len));
}

/*
** takes t_range and looks for t_bash_pattern_type with longest fixed size
** - t_range is expected to contain index of begin and end of the lexer/parser
**   tokens to match on
*/

t_bash_pattern_type		bash_match_pattern(t_range range)
{
	const size_t		pat_list_size = sizeof(pat_list)/sizeof(pat_list[0]);
	t_bash_pattern		*candidate;
	size_t				i;
	
	assert(range.end >= range.begin);
	candidate = NULL;
	i = 0;
	while (i < pat_list_size)
	{
		if (is_bash_pattern(range, &pat_list[i]))
		{
			/* we found a match */
			if (candidate == NULL || pat_list[i].fixed_types_len > candidate->fixed_types_len)
			{
				/* this candidate is better */
				candidate = (t_bash_pattern *)&pat_list[i];
			}
		}
		i++;
	}
	return ((candidate == NULL) ? P_NO_TYPE : candidate->pattern_type);
}

char					*pattern_dump_type(t_bash_pattern_type type)
{
	switch (type)
	{
		case P_COMMAND:
			return ("COMMAND");
		case P_PATH:
			return ("PATH");
		case P_ASSIGNMENT:
			return ("ASSIGNMENT");
		case P_NO_TYPE:
			return ("NO_TYPE");
		default:
			return (NULL);
	}
}
