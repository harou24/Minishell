#include <stdlib.h>
#include "libft.h"
#include "parser.h"

# define V_DEF_SIZE 128

static t_parser *g_parser__;

t_token			*parse_substitute_var(t_vector tokens, t_token *var_name)
{
	/* need access to env hashmap here */
	(void)tokens;
	return (var_name);
}

/* helper function for parse_expand_first_string */
t_vector		parse_get_subtokens(t_token *first, t_token *last)
{
	t_vector	subtokens;
	
	subtokens = vector(&subtokens, V_CREATE, V_DEF_SIZE, NULL);
	if (!subtokens)
		return (NULL);
	while(first->next && first->next != last)
	{
		vector(&subtokens, V_PUSHBACK, 0, first->next);
		first = first->next;
	}
	return (subtokens);	
}

/* helper function for parse_expand_first_string */
int				has_variable_token(void *obj)
{
	t_token *token;

	token = (t_token *)obj;
	return (token->type == VARIABLE);
}

/* helper function for parse_expand_first_string */
void			parse_remove_subtokens(t_vector tokens, t_token *first, t_token *last)
{
	const size_t index_of_first = first->index;
	size_t index;

	index = last->index;
	while(index >= index_of_first)
	{
		vector(&tokens, V_POPAT, index, NULL);
		index--;
	}
}

/*
void			parse_perform_string_substitution(	t_vector tokens,
													t_token *first,
													t_token *last,
													t_vector subtokens)
{
	char		*string;
	char		*extra;
	char		*tmp_string;
	t_token		*tmp_token;
	size_t		index;
	t_token		*token;

	token = token_create(range(first->range.begin, last->range.end), STRING);

	index = 0;
	string = ft_strdup("");
	while (vector(&subtokens, V_PEEKAT, index, NULL))
	{
		tmp_token = vector(&subtokens, V_PEEKAT, index, NULL);
		tmp_string = string;
		extra = ft_strsub()
		string = ft_strjoin(string, );
	}

	parse_remove_subtokens(tokens, first, last);
}
*/

t_bool			parse_expand_first_string(t_journal *journal, t_vector tokens, t_token *first, t_token *last)
{
	t_vector subtokens;

	subtokens = parse_get_subtokens(first, last);

	if (vector(&subtokens, V_FIND_NTH, 0, (void *)has_variable_token))
	{
		/* expand variable here */
	}
	else
	{
		/* stitch everything together */
		/* parse_perform_string_substitution(tokens, first, last, subtokens); */
	}
	
	vector(&subtokens, V_DESTROY, 0, NULL);
	return (FALSE);
	(void)journal; /* needed for substr*/
	(void)tokens; /* substitution */
}

t_bool			parse_expand_strings(t_journal *journal)
{
	t_vector *tokens;

	if (journal_has_tokentype(QUOTE) == 0)
		return (TRUE);
	if (!journal_has_tokentype(QUOTE) % 2 != 0)
		return (FALSE);
	tokens = journal_get_token_vector();
	while (journal_has_tokentype(QUOTE) > 0)
		parse_expand_first_string(journal, tokens, journal_find_nth_type(QUOTE, 0), journal_find_nth_type(QUOTE, 1));	
	return (TRUE);
}

t_execscheme	*parse(t_journal *journal)
{
	(void)journal;
	return (NULL);
}

t_parser	*parser_create()
{
	t_parser *parser;

	if (g_parser__)
		return (g_parser__);
	parser = ft_calloc(sizeof(t_parser), 1);
	if (parser)
	{
	}
	return ((g_parser__ = parser));
}

t_parser	*parser_destroy(t_parser **parser)
{
	if (!g_parser__)
		return (NULL);
	execscheme_destroy(&g_parser__->scheme);
	free(g_parser__);
	g_parser__ = NULL;
	if (parser)
		*parser = NULL;
	return ((g_parser__ = NULL));
}
