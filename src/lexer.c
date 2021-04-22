/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:03:10 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:03:12 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "vector.h"
#include "debugger.h"
#include "lexer.h"
#include "token.h"
#include "bash_sym.h"

extern t_lex	*g_lex__;

static t_token	*lex_get_next_token(void)
{
	const size_t	og_index = g_lex__->index;
	size_t			slen;
	t_token_type_e	og_type;
	t_token_type_e	type;

	slen = 1;
	og_type = bash_match(&g_lex__->input[g_lex__->index], slen);
	if (og_type == NO_TYPE || g_lex__->index + slen > g_lex__->input_len)
		return (NULL);
	type = og_type;
	while (type == og_type && g_lex__->index + slen <= g_lex__->input_len)
	{
		slen++;
		type = bash_match(&g_lex__->input[g_lex__->index], slen);
	}
	if (slen > 1)
		slen -= 1;
	g_lex__->index += slen;
	if (slen > 0)
		slen -= 1;
	return (token_create(range(og_index, og_index + slen), og_type));
}

static void	lex_add_nullbyte(void)
{
	t_token		*token;

	token = token_create(range(g_lex__->index, g_lex__->index), NULLBYTE);
	assert(token);
	journal_push(token);
}

static t_journal	*lex_build_journal(char *str)
{
	t_token	*token;

	journal_set_input_str(str);
	token = lex_get_next_token();
	while (token)
	{
		journal_push(token);
		token = lex_get_next_token();
	}
	lex_add_nullbyte();
	journal_build_linked_list();
	return (g_lex__->journal);
}

t_journal	*lex(const char *str)
{
	if (!g_lex__)
		return (NULL);
	lex_clear();
	g_lex__->input = ft_strdup(str);
	g_lex__->input_len = ft_strlen(g_lex__->input);
	dbg("Lexing string: '%s'\n", g_lex__->input);
	return (lex_build_journal(g_lex__->input));
}
