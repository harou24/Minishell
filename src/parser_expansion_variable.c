/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_expansion_variable.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:03:59 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:04:01 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>

#include "env_singleton.h"
#include "parser.h"

extern t_parser	*g_parser__;

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

static t_bool	parse_can_be_variable_name(t_token *var_name)
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
	if (!parse_can_be_variable_name(var_name))
	{
		var_sym->type = WORD;
		journal_rebuild_tokens();
		return (TRUE);
	}
	parse_perform_var_substitution(tokens, var_sym, var_name);
	return (TRUE);
}

static t_bool	is_variable_in_matcharea(void)
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
