#include <assert.h>

#include "env_singleton.h"
#include "parser.h"

extern t_parser	*g_parser__;

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

t_bool	parse_is_variable(t_token *var_name)
{
	assert(var_name);
	return (var_name && (var_name->type == WORD || var_name->type == SYM
			|| var_name->type == ASSIGNMENT || var_name->type == VARIABLE));
}

t_bool	parse_expand_first_variable(t_vector tokens, t_token *var_sym)
{
	const size_t	var_sym_index = var_sym->index;
	t_token			*var_name;

	var_name = journal_get(var_sym_index + 1);
	if (!parse_is_variable(var_name))
	{
		var_sym->type = WORD;
		journal_rebuild_tokens();
		return (TRUE);
	}
	parse_perform_var_substitution(tokens, var_sym, var_name);
	return (TRUE);
}

static t_bool is_variable_in_matcharea(void)
{
	return (journal_find_nth_type(VARIABLE, 0)->index + 1
		<= g_parser__->matcharea.end);
}

t_bool	parse_expand_variables(void)
{
	t_vector	*tokens;

	if (journal_has_tokentype(VARIABLE) == 0)
		return (TRUE);
	tokens = journal_get_token_vector();
	while (journal_has_tokentype(VARIABLE) > 0 && is_variable_in_matcharea())
	{
		assert(journal_find_nth_type(VARIABLE, 0));
		if (journal_find_nth_type(VARIABLE, 0)->index
			>= g_parser__->matcharea.end)
			break ;
		parse_expand_first_variable(tokens, journal_find_nth_type(VARIABLE, 0));
	}
	return (TRUE);
}
