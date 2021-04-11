#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "debugger.h"
#include "bash_pattern.h"
#include "parser.h"
#include "env_singleton.h"

#define VEC_SIZE 128

t_parser	*g_parser__;

t_vector	parse_get_subtokens(t_token *first, t_token *last)
{
	t_vector	subtokens;

	assert(first);
	assert(last);
	vector(&subtokens, V_CREATE, VEC_SIZE, NULL);
	if (!subtokens)
		return (NULL);
	while (first->next && first->next != last)
	{
		vector(&subtokens, V_PUSHBACK, 0, first->next);
		first = first->next;
	}
	return (subtokens);
}

void	parse_replace_tokens_with_token(t_vector tokens, t_token *first,
						t_token *last, t_token *token)
{
	const ssize_t	index_of_first = first->index;
	ssize_t			index;

	index = last->index;
	assert(index > 0);
	while (index >= index_of_first)
	{
		token_destroy(vector(&tokens, V_POPAT, index, NULL));
		index--;
	}
	if (index_of_first < (ssize_t)journal_size())
		vector(&tokens, V_PUSHAT, (size_t)index_of_first, token);
	else
		vector(&tokens, V_PUSHAT, journal_size(), token);
	assert(journal_size() > 0);
	journal_rebuild_tokens();
}
