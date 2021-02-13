#include "token.h"

/* is token always the smallest token ? */

/*
t_bool		token_find_in_str(const char *str, size_t begin, size_t len)
{
	
}
*/

t_bool		token_cmp(const t_token *a, const t_token *b)
{
	return (a->type == b->type);
	/* return (ft_memcmp(a, b, sizeof(t_token) == 0)); */
}

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
