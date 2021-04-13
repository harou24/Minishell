#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "debugger.h"
#include "bash_pattern.h"
#include "parser.h"
#include "env_singleton.h"

#define VEC_SIZE 128

t_parser	*g_parser__ = NULL;

t_execscheme	*parse(t_range matcharea)
{
	if (range_cmp(matcharea, range(0, 0)) == 0)
		return (NULL);
	g_parser__->matcharea = matcharea;
	parse_dump_match_area(g_parser__->matcharea);
	if (!parse_expand())
	{
		dbg("Failed to expand!\n", "");
		return (NULL);
	}
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
