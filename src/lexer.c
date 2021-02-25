#include <assert.h>
#include "vector.h"
#include "lexer.h"
#include "token.h"
#include "bash_sym.h"

static t_lex * g_lex__;

t_journal	*lex(const char *str)
{
	if (!g_lex__)
		return (NULL);
	lex_clear();
	g_lex__->input = ft_strdup(str);
	g_lex__->input_len = ft_strlen(str);
	return (lex_build_journal(str));
}

t_token     *lex_get_next_token()
{
	const size_t	og_index = g_lex__->index;
	size_t			slen;
	e_token_type	og_type;
	e_token_type	type;

	slen = 1;
	og_type = bash_match(&g_lex__->input[g_lex__->index], slen);
	if(og_type == NO_TYPE || g_lex__->index + slen > g_lex__->input_len)
		return (NULL);
	type = og_type;
	while(type == og_type && g_lex__->index + slen <= g_lex__->input_len)
	{
		slen++;
		type = bash_match(&g_lex__->input[g_lex__->index], slen);
	}
	slen -= ((slen > 1) ? 1 : 0);
	g_lex__->index += slen;
	slen -= ((slen > 0) ? 1 : 0); /* wtf is going on here */
	return (token_create(range(og_index, og_index + slen), og_type));
}

void		lex_add_nullbyte()
{
	t_token *token;

	assert(g_lex__->input[g_lex__->index] == '\0');
	token = token_create(range(g_lex__->index, g_lex__->index), NULLBYTE);
	assert(token);
	journal_push(token);
}

t_journal   *lex_build_journal(char *str)
{
	t_token *token;
	
	journal_set_input_str(str);
	while ((token = lex_get_next_token()))
	{
		journal_push(token);
	}
	lex_add_nullbyte();
	journal_build_linked_list();
	return (g_lex__->journal);
}

void		lex_clear()
{
	if (g_lex__)
	{
		free(g_lex__->input);
		g_lex__->input = NULL;
		g_lex__->index = 0;
		journal_clear();
	}
}

t_lex		*lex_create()
{
	t_lex *lex;

	if (g_lex__)
		return (g_lex__);
	lex = ft_calloc(sizeof(t_lex), 1);
	if (lex)
	{
		lex->journal = journal_create();
		if  (!lex->journal /*|| !lex->keystore */)
			return (lex_destroy(&lex));
	}
	return (( g_lex__ = lex));
}

t_lex		*lex_destroy(t_lex **lex)
{
	if (!g_lex__)
		return (NULL);
	journal_destroy(&g_lex__->journal);
	/*hm_destroy(lex->keystore); */
	free(g_lex__->input);
	free(g_lex__);
	g_lex__ = NULL;
	if (lex)
		*lex = NULL;
	return ((g_lex__ = NULL));
}
