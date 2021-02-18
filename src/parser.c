#include <stdlib.h>
#include "libft.h"
#include "parser.h"

static t_parser *g_parser__;

t_execscheme	*parse(t_journal *journal)
{

}

t_parser	*parser_create()
{
	t_parser *parser;

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
	execscheme_destroy(&g_parser__->journal);
	free(g_parser__);
	g_parser__ = NULL;
	if (parser)
		*parser = NULL;
	return ((g_parser__ = NULL));
}
