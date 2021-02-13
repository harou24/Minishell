#include "vector.h"
#include "lexer.h"
#include "token.h"

static t_lex * g_lex__;

t_journal	*lex(const char *str)
{
	g_lex__ = lex_create();
	if (!g_lex__)
		return (NULL);
	(void)str;
	return (NULL);
}

t_journal	*lex_for(t_lex *lex, const char *str)
{
	(void)str;
	(void)lex;
	return (NULL);
}

t_lex		*lex_create()
{
	/* return local static g_lex__ */
	if (g_lex__ != NULL)
		return (g_lex__);
	else
		return ((g_lex__ = lex_create_for()));
}

t_lex		*lex_create_for()
{
	t_lex *lex;

	lex = ft_calloc(sizeof(t_lex), 1);
	if (lex)
	{
		lex->journal = journal_create(TOKEN_TYPE_INDEX + 1);
		if  (!lex->journal)
			return (lex_destroy(lex));
	}
	return (lex);
}

t_lex		*lex_destroy()
{
	if (!g_lex__)
		return (NULL);
	lex_destroy(g_lex__);
	return ((g_lex__ = NULL));
}

t_lex		*lex_destroy_for(t_lex *lex)
{
	journal_destroy(lex->journal);
	free(lex);
	return (NULL);
}
