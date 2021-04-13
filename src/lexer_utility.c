#include "lexer.h"

extern t_lex	*g_lex__;

void	lex_clear(void)
{
	if (g_lex__)
	{
		free(g_lex__->input);
		g_lex__->input = NULL;
		g_lex__->index = 0;
		journal_clear();
	}
}
