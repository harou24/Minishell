#include "vector.h"
#include "lexer.h"

t_bool		lexer(t_lexer *lex, const char *str)
{
	(void)str;
	(void)lex;
	return (FALSE);
}

t_lexer		*lexer_create()
{
	t_lexer *lex;

	lex = ft_calloc(sizeof(t_lexer), 1);
	if (lex)
	{
		if (!vector(&lex->tokens, V_CREATE, g_lexer_default_size, NULL))
			return (lexer_destroy(lex));
	}
	return (lex);
}

t_lexer		*lexer_destroy(t_lexer *lex)
{
	while (*(size_t *)vector(&lex->tokens, V_SIZE, 0, 0) > 0)
	{
		token_destroy(vector(&lex->tokens, V_PEEKBACK, 0, 0));
		vector(&lex->tokens, V_POPBACK, 0, 0);
	}
	vector(&lex->tokens, V_DESTROY, FALSE, 0);
	free(lex);
	return (NULL);
}
