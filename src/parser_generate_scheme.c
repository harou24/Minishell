/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_generate_scheme.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:04:07 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/14 21:04:15 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#include "libft.h"

#include "debugger.h"
#include "bash_pattern.h"
#include "parser.h"

extern t_parser	*g_parser__;

t_exec_op_type	parse_get_op_type_for_pattern(t_range area,
						t_bash_pattern_type pat_type)
{
	if (pat_type == P_COMMAND)
	{
		if (journal_get(area.begin)->type == SPACE)
			area.begin++;
		return (execscheme_get_op_type_for_token(journal_get(area.begin)));
	}
	else if (pat_type == P_ASSIGNMENT)
		return (OP_ASSIGNMENT);
	return (OP_NO_TYPE);
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
		scheme->cmd = command_create(parse_build_path(&area));
		if (!parse_extract_command_arguments(scheme->redir, scheme->cmd, area))
		{
			dbg("Failed to extract command arguments!\n", "");
			execscheme_destroy(&scheme);
			return (NULL);
		}
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

t_execscheme	*parse_generate_execschemes(void)
{
	t_execscheme	*root;
	t_execscheme	*scheme;

	root = NULL;
	scheme = parse_get_next_scheme();
	while (scheme)
	{
		if (!root)
		{
			root = scheme;
			scheme->rel_type[PREV_R] = REL_START;
		}
		else
		{
			execscheme_attach(root, scheme);
		}
		scheme = parse_get_next_scheme();
	}
	if (!root)
		dbg("Failed to build execschemes!\n", "");
	parse_flush_tokens(g_parser__->matcharea);
	return (root);
}
