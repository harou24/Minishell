#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

# define V_DEF_SIZE 128

#include <stdio.h>

static t_parser *g_parser__;

char			*parse_get_variable_for_token(t_token *token)
{
	char *key;
	char *var;

	key = ft_strsub(journal_get_input_str(), token->range.begin, 1 + token->range.end - token->range.begin);
	assert(key);

	/* env call here */
	var = ft_strdup("PLACEHOLDER");

	free(key);
	return(var);
}

void			parse_perform_var_substitution(t_vector tokens, t_token *var_sym, t_token *var_name)
{
	t_token *token;
	
	assert(var_sym->index == var_name->index - 1);
	token = token_create(range(var_name->range.begin - 1, var_name->range.end), WORD);
	assert(token);

	token->string = parse_get_variable_for_token(var_name);
	assert(token->string);

	parse_replace_tokens_with_token(tokens, var_sym, var_name, token);
}

/* helper function for parse_expand_first_string */
t_vector		parse_get_subtokens(t_token *first, t_token *last)
{
	t_vector	subtokens;
	
	assert(first);
	assert(last);
	/* printf("parse get subtokens called!\n"); */
	vector(&subtokens, V_CREATE, V_DEF_SIZE, NULL);
	assert(subtokens);
	if (!subtokens)
		return (NULL);
	while(first->next && first->next != last)
	{
		/* printf("get_subtokens: token : %s\n", token_dump_type(first->next->type)); */
		vector(&subtokens, V_PUSHBACK, 0, first->next);
		first = first->next;
		/* printf("parse get subtokens : loop\n"); */
	}
	return (subtokens);	
}

/* this can fuck off? */
/* helper function for parse_expand_first_string */
int				has_variable_token(void *obj)
{
	t_token *token;

	token = (t_token *)obj;
	return (token->type == VARIABLE);
}

/* helper function for parse_expand_first_string */
void			parse_replace_tokens_with_token(t_vector tokens, t_token *first, t_token *last, t_token *token)
{
	const ssize_t index_of_first = first->index;
	ssize_t index;

	/*printf("parse_replace_tokens_with_token called! : first:{%s}{%lu}, last:{%s}{%lu}\n", token_dump_type(first->type), first->index, token_dump_type(last->type), last->index); */

	index = last->index;
	assert(index > 0);
	/* printf("index : %lu\n", index); */
	while(index >= index_of_first)
	{
		/* printf("parse_replacE_tokens_with_token called! : loop index : %li\n", index); */
		token_destroy(vector(&tokens, V_POPAT, index, NULL));
		index--;
	}
	/* printf("parse_replaceE_tokens_with_token: pushing toking to index : %li, size: %lu\n", index_of_first, journal_size()); */
	assert(vector(&tokens, V_PUSHAT, (index_of_first < (ssize_t)journal_size()) ? (size_t)index_of_first : journal_size(), token));
	assert(journal_size() > 0);
	journal_rebuild_tokens();
}

void			parse_perform_string_substitution(	t_vector tokens,
													t_token *first,
													t_token *last,
													t_vector subtokens)
{
	char		*string;
	t_token		*tmp_token;
	size_t		index;
	t_token		*token;

	assert(first);
	assert(last);
	assert(tokens);
	assert(subtokens);

	token = token_create(range(first->range.begin, last->range.end), WORD);

	index = 0;
	string = NULL;
	/* printf("subtoken size: %lu\n", *(size_t *)vector(&subtokens, V_SIZE, 0, NULL) ); */
	while (vector(&subtokens, V_PEEKAT, index, NULL))
	{
		tmp_token = vector(&subtokens, V_PEEKAT, index, NULL);

		string = ft_strjoin_noreuse(string, journal_get_string_for_token(tmp_token));
		/* printf("string in loop : %s\n", string); */
		index++;
	}
	/* printf("resulting string : \"%s\"\n", string); */
	token->string = (string != NULL) ? string : ft_strdup("");
	parse_replace_tokens_with_token(tokens, first, last, token);
}

t_bool			parse_expand_first_string(t_vector tokens, t_token *first, t_token *last)
{
	t_vector subtokens;

	assert(tokens);
	assert(first);
	assert(last);
	assert(first != last);

	subtokens = parse_get_subtokens(first, last);
	assert(subtokens);

	/* stitch everything together */
	parse_perform_string_substitution(tokens, first, last, subtokens);
	
	vector(&subtokens, V_DESTROY, 0, NULL);
	return (FALSE);
}

t_bool			parse_expand_strings(e_token_type string_type)
{
	t_vector *tokens;

	if (journal_has_tokentype(string_type) == 0)
		return (TRUE);

	/* printf("parse_expand_strings: journal_has_token_type(QUOTE) : %i\n", journal_has_tokentype(QUOTE)); */
	if (!(journal_has_tokentype(string_type) % 2 == 0))
		return (FALSE);
	tokens = journal_get_token_vector();
	while (journal_has_tokentype(string_type) > 0)
	{
		/* printf("parse_expand_strings : loop, still has : %i tokens\n", journal_has_tokentype(QUOTE)); */
		assert(journal_has_tokentype(string_type) % 2 == 0);
		parse_expand_first_string(tokens, journal_find_nth_type(string_type, 0), journal_find_nth_type(string_type, 1));	
	}

	return (TRUE);
}

t_bool			parse_expand_first_variable(t_vector tokens, t_token *var_sym)
{
	assert(tokens);
	assert(var_sym);

	const size_t	var_sym_index = var_sym->index;
	t_token			*var_name;

	var_name = journal_get(var_sym_index + 1);
	if (!var_name || var_name->type != WORD)
	{
		/* this was just a $ sign */
		/* printf("parse_expand_first_variable : was just a $ sign!\n"); */
		var_sym->type = WORD;
		journal_rebuild_tokens();
		return (TRUE);
	}
	parse_perform_var_substitution(tokens, var_sym, var_name);
	return (TRUE);
}

t_bool			parse_expand_variables()
{
	t_vector *tokens;

	if (journal_has_tokentype(VARIABLE) == 0)
		return (TRUE);

	/* printf("parse_expand_variables: journal_has_token_type(VARIABLE) : %i\n", journal_has_tokentype(VARIABLE)); */
	tokens = journal_get_token_vector();

	while (journal_has_tokentype(VARIABLE) > 0)
	{
		/* printf("parse_expand_variables : loop, still has : %i variables\n", journal_has_tokentype(VARIABLE)); */
		assert(journal_find_nth_type(VARIABLE, 0));
		parse_expand_first_variable(tokens, journal_find_nth_type(VARIABLE, 0));	
	}
	return (TRUE);
}

t_bool			parse_should_expand_literals()
{
	t_token		*string;
	t_token		*literal;
	
	string = journal_find_nth_type(STRING, 0);
	literal = journal_find_nth_type(LITERAL, 0);

	return (string && literal && string->index > literal->index);
}

void			parse_expand()
{
	if (parse_should_expand_literals())
		parse_expand_strings(LITERAL);
	parse_expand_variables();
	parse_expand_strings(STRING);
}

t_execscheme	*parse()
{
	parse_expand();
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
