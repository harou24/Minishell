/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_lifetime.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:03:22 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:03:24 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lex	*g_lex__ = NULL;

t_lex	*lex_create(void)
{
	t_lex	*lex;

	if (g_lex__)
		return (g_lex__);
	lex = ft_calloc(sizeof(t_lex), 1);
	if (lex)
	{
		lex->journal = journal_create();
		if (!lex->journal)
			return (lex_destroy(&lex));
	}
	return ((g_lex__ = lex));
}

t_lex	*lex_destroy(t_lex **lex)
{
	if (!g_lex__)
		return (NULL);
	journal_destroy(&g_lex__->journal);
	free(g_lex__->input);
	free(g_lex__);
	g_lex__ = NULL;
	if (lex)
		*lex = NULL;
	return ((g_lex__ = NULL));
}
