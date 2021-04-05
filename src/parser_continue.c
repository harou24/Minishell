#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "parser.h"

extern t_parser	*g_parser__;

t_execscheme	*parse_generate_execschemes(void)
{
	t_execscheme	*root;
	t_execscheme	*scheme;

	root = NULL;
	parse_reset_match_area();
	parse_dump_match_area(g_parser__->matcharea);
	scheme = parse_get_next_scheme();
	while (scheme)
	{
		if (!root)
		{
			root = scheme;
			scheme->rel_type[PREV_R] = REL_START;
		}
		else
			execscheme_attach(root, scheme);
		scheme = parse_get_next_scheme();
	}
	return (root);
}

t_execscheme	*parse(void)
{
	if (!parse_expand())
		return (NULL);
	if (g_parser__->rootscheme)
		execscheme_destroy(&g_parser__->rootscheme);
	g_parser__->rootscheme = parse_generate_execschemes();
	return (g_parser__->rootscheme);
}

t_parser	*parser_create(void)
{
	t_parser	*parser;

	if (g_parser__)
		return (g_parser__);
	parser = ft_calloc(sizeof(t_parser), 1);
	if (parser)
	{
	}
	return ((g_parser__ = parser));
}

t_parser	*parser_destroy(t_parser **parser)
{
	if (!g_parser__)
		return (NULL);
	execscheme_destroy(&g_parser__->rootscheme);
	free(g_parser__);
	g_parser__ = NULL;
	if (parser)
		*parser = NULL;
	return ((g_parser__ = NULL));
}

void	parser_set_env(t_env *env)
{
	assert(g_parser__);
	assert(! g_parser__->env);
	g_parser__->env = env;
}
