#include <assert.h>
#include <stdlib.h>

#include "parser.h"
#include "env_singleton.h"

extern t_parser	*g_parser__;

void	parse_perform_string_substitution(t_vector tokens, t_token *first,
						t_token *last, t_vector subtokens)
{
	char		*string;
	t_token		*cur_token;
	size_t		index;
	t_token		*token;

	assert(first);
	assert(last);
	assert(tokens);
	assert(subtokens);
	token = token_create(range(first->range.begin, last->range.end), WORD);
	index = 0;
	string = NULL;
	cur_token = vector(&subtokens, V_PEEKAT, index, NULL);
	while (cur_token)
	{
		string = ft_strjoin_noreuse(string,
				journal_get_string_for_token(cur_token));
		index++;
		cur_token = vector(&subtokens, V_PEEKAT, index, NULL);
	}
	if (string != NULL)
		token->string = string;
	else
		token->string = ft_strdup("");
	parse_replace_tokens_with_token(tokens, first, last, token);
}

t_bool	parse_expand_first_string(t_vector tokens,
					t_token *first, t_token *last)
{
	t_vector	subtokens;

	assert(tokens);
	assert(first);
	assert(last);
	assert(first != last);
	subtokens = parse_get_subtokens(first, last);
	assert(subtokens);
	parse_perform_string_substitution(tokens, first, last, subtokens);
	vector(&subtokens, V_DESTROY, FALSE, NULL);
	return (TRUE);
}

t_bool	parse_expand_strings(e_token_type string_type)
{
	t_vector	*tokens;

	if (journal_has_tokentype(string_type) == 0)
		return (TRUE);
	if (!(journal_has_tokentype(string_type) % 2 == 0))
		return (FALSE);
	tokens = journal_get_token_vector();
	while (journal_has_tokentype(string_type) > 0)
		parse_expand_first_string(tokens,
			journal_find_nth_type(string_type, 0),
			journal_find_nth_type(string_type, 1));
	return (TRUE);
}

char	*parse_retreive_var_from_env_for_token(t_token *token)
{
	char	*key;
	char	*var;

	key = ft_strsub(journal_get_input_str(),
			token->range.begin, 1 + token->range.end - token->range.begin);
	assert(key);
	var = env_get_s(key);
	if (var == NULL)
		var = ft_strdup("");
	else
		var = ft_strdup(var);
	free(key);
	return (var);
}

void	parse_perform_var_substitution(t_vector tokens,
					t_token *var_sym, t_token *var_name)
{
	t_token	*token;

	assert(var_sym->index == var_name->index - 1);
	token = token_create(
			range(var_name->range.begin - 1, var_name->range.end), WORD);
	assert(token);
	token->string = parse_retreive_var_from_env_for_token(var_name);
	assert(token->string);
	parse_replace_tokens_with_token(tokens, var_sym, var_name, token);
}
