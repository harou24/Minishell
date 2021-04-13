#include <assert.h>
#include <stdlib.h>

#include "debugger.h"
#include "libft.h"

#include "parser.h"

extern t_parser	*g_parser__;

t_bool	parse_is_token_in_matcharea(t_token *token)
{
	return (token && token->index <= g_parser__->matcharea.end);
}
