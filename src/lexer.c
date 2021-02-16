#include "vector.h"
#include "lexer.h"
#include "token.h"
#include "bash_sym.h"

static t_lex * g_lex__;

t_journal	*lex(const char *str)
{
	if (!g_lex__)
		return (NULL);
	if (g_lex__->input)
		free(g_lex__->input);
	g_lex__->input = ft_strdup(str);
	g_lex__->input_len = ft_strlen(str);
	return (lex_build_journal());
}

t_token     *lex_get_next_token()
{
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
	g_lex__->index += slen - ((slen > 1) ? 1 : 0);
	return (token_create(range(g_lex__->index, g_lex__->index + slen), og_type));
}

t_journal   *lex_build_journal()
{
	t_token *token;



	while ((token = lex_get_next_token()))
	{
		journal_push(token);
	}
	return (g_lex__->journal);
}

void		lex_clear()
{
	if (g_lex__)
	{
		g_lex__->index = 0;
		free(g_lex__->input);
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
		/* lex->keystore = hm_new(1024); */
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
