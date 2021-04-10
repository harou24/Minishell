#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "debugger.h"
#include "bash_pattern.h"
#include "parser.h"

extern t_parser	*g_parser__;

t_exec_op_type	parse_get_op_type_for_pattern(t_range area,
						t_bash_pattern_type pat_type)
{
	t_exec_op_type	op_type;

	if (pat_type == P_COMMAND || pat_type == P_PATH)
	{
		if (journal_get(area.begin)->type == SPACE)
			area.begin++;
		op_type = execscheme_get_op_type_for_token(journal_get(area.begin));
	}
	else if (pat_type == P_ASSIGNMENT)
		op_type = OP_ASSIGNMENT;
	else if (pat_type == P_PATH)
		op_type = OP_PATH;
	else
		op_type = OP_NO_TYPE;
	return (op_type);
}

t_execscheme	*parse_build_execscheme(t_range area,
					t_bash_pattern_type pat_type)
{
	t_execscheme	*scheme;

	scheme = execscheme_create();
	if (scheme)
	{
		scheme->rel_type[NEXT_R] = execscheme_get_relation_type_for_token(
				journal_get(area.end));
		scheme->op_type = parse_get_op_type_for_pattern(area, pat_type);
		scheme->cmd = parse_build_command(area);
		assert(scheme->cmd);
	}
	return (scheme);
}

t_execscheme	*parse_get_next_scheme(void)
{
	t_range				my_area;
	t_bash_pattern_type	pat_type;

	my_area = g_parser__->matcharea;
	while (my_area.end > my_area.begin)
	{
		pat_type = bash_match_pattern(range(my_area.begin, my_area.end - 1));
		if (pat_type != P_NO_TYPE)
		{
			dbg("Found pattern %s for range {%i, %i}\n",
				pattern_dump_type(pat_type), my_area.begin, my_area.end);
			g_parser__->matcharea.begin = my_area.end + 1;
			return (parse_build_execscheme(my_area, pat_type));
		}
		my_area.end--;
	}
	return (NULL);
}

void	parse_reset_match_area(void)
{
	g_parser__->matcharea = range(0, journal_size());
}

void	parse_dump_match_area(t_range area)
{
	char	*range;
	char	*tokens;

	range = range_dump(area);
	tokens = journal_dump_tokens_for_range(area);
	dbg("area: %s, tokens: %s\n", range, tokens);
	free(range);
	free(tokens);
}
