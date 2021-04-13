/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_expansion_variable_continue.c               :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:04:03 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:04:05 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
