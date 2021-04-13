/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   journal_find_continue.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:02:38 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:02:40 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

t_token	*journal_find_nth_token(const t_token *token, int n)
{
	return (journal_find_nth_type(token->type, n));
}
