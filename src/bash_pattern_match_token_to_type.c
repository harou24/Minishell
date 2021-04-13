/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bash_pattern_match_token_to_type.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:56:33 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:56:35 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bash_pattern.h"

t_bool	match_token_to_type(t_token *token, const t_token_type_e type)
{
	return (token->type == type);
}
