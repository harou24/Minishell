#include <assert.h>
#include <stdlib.h>
#include "libft.h"
#include "execscheme.h"

void			execscheme_attach(t_execscheme *root, t_execscheme *scheme)
{
	assert(root);
	assert(scheme);

	while (root->next)
		root = root->next;
	root->next = scheme;
}

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
	if (*execscheme)
	{
		command_destroy(&(*execscheme)->cmd);
		free(*execscheme);
	}
	return ((*execscheme = NULL));
}
