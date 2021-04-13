#include "lexer.h"

t_lex	*g_lex__;

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
