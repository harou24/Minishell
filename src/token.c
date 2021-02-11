#include "token.h"

t_token		*token_create()
{
	t_token *token;

	token = ft_calloc(sizeof(t_token), 1);
	if (token)
	{

	}
	return (token);
}

t_token		*token_destroy(t_token *token)
{
	free(token);
	return (NULL);
}
