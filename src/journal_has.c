/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   journal_has.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:02:42 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:02:43 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

int	journal_has_token(const t_token *token)
{
	return (journal_has_tokentype(token->type));
}

int	journal_has_tokentype(const t_token_type_e type)
{
	return (g_journal__->counter[type]);
}
