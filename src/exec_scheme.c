#include "exec_scheme.h"


t_execscheme	*execscheme_create()
{
	t_execscheme *scheme;

	scheme = ft_calloc(sizeof(t_execscheme), 1);
	if (scheme)
	{

	}
	return (scheme);
}

t_execscheme	*execscheme_destroy(t_execscheme **execscheme)
{
	if (!execscheme)
		return (NULL);
	free(*execscheme);
	return ((*execscheme = NULL));
}
