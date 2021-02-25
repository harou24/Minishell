#include <stdlib.h>
#include <assert.h>
#include "bash_pattern.h"

static const t_bash_pattern pat_list[] =	{
												{ P_COMMAND, 2, {WORD, SPACE}, 2, {WORD, SPACE} },
												{ P_ASSIGNMENT, 4, {WORD, SPACE, ASSIGNMENT, WORD}, 0, {} }
											};

t_bool					match_fuzzy(t_range range, const e_token_type *fixed_types, size_t fixed_types_len)
{
	/* stub */
	(void)range;
	(void)fixed_types;
	(void)fixed_types_len;
	return (FALSE);
}

t_bool					match_fixed(t_range range, const e_token_type *fixed_types, size_t fixed_types_len)
{
	size_t				i;
	t_token				*token;

	if (range.end >= journal_size() || range.end + range.begin > fixed_types_len)
		return (FALSE);
	range.end += fixed_types_len;
	i = 0;
	while (range.begin + i <= range.end)
	{
		token = journal_get(range.begin + i);
		assert(token);
		if (fixed_types[i] != token->type)
			return (FALSE);
		i++;	
	}
	return (TRUE);
}

t_bool					is_bash_pattern(t_range range, const t_bash_pattern *pattern)
{
	return (match_fixed(range, pattern->fixed_types, pattern->fixed_types_len)
		&& match_fuzzy(range, pattern->fuzzy_types, pattern->fuzzy_types_len));
}

t_bash_pattern_type		batch_match_pattern(t_journal *journal, t_range range)
{
	const size_t	pat_list_size = sizeof(pat_list)/sizeof(pat_list[0]);
	t_bash_pattern	*candidate;
	size_t			i;

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
	(void)journal;
}
