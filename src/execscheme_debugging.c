/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execscheme_debugging.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:00:51 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:00:53 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execscheme.h"
#include "debugger.h"

static char	*g_op_types__[OP_TAB_SIZE] = {
		[OP_COMMAND] = "OP_COMMAND",
		[OP_PATH] = "PATH",
		[OP_ASSIGNMENT] = "OP_ASSIGNMENT",
		[OP_BUILTIN_ECHO] = "OP_BUILTIN_ECHO",
		[OP_BUILTIN_CD] = "OP_BUILTIN_CD",
		[OP_BUILTIN_PWD] = "OP_BUILTIN_PWD",
		[OP_BUILTIN_EXPORT] = "OP_BUILTIN_EXPORT",
		[OP_BUILTIN_UNSET] = "OP_BUILTIN_UNSET",
		[OP_BUILTIN_ENV] = "OP_BUILTIN_ENV",
		[OP_BUILTIN_EXIT] = "OP_BUILTIN_EXIT",
		[OP_NO_TYPE] = "NO_TYPE"
};

static char	*g_relation_types__[REL_TAB_SIZE] = {
		[REL_START] = "REL_START",
		[REL_SEQ] = "REL_SEQ",
		[REL_PIPE] = "REL_PIPE",
		[REL_READ] = "REL_READ",
		[REL_APPEND] = "REL_APPEND",
		[REL_WRITE] = "REL_WRITE",
		[REL_NO_TYPE] = "NO_TYPE",
		[REL_END] = "REL_END"
};

const char	*execscheme_dump_op_type(t_exec_op_type type)
{
	return (g_op_types__[type]);
}

const char	*execscheme_dump_relation_type(t_exec_relation_type type)
{
	return (g_relation_types__[type]);
}

void	execscheme_pretty_dump(t_execscheme *root, int indent)
{
	while (root)
	{
		dbg("%*s :\n", indent, "Scheme");
		dbg("%*s : %s\n", (int)(indent * 1.5), "OP",
			execscheme_dump_op_type(root->op_type));
		dbg("%*s : %s\n", (int)(indent * 1.5), "REL_PREV",
			execscheme_dump_relation_type(root->rel_type[PREV_R]));
		dbg("%*s : %s\n", (int)(indent * 1.5), "REL_NEXT",
			execscheme_dump_relation_type(root->rel_type[NEXT_R]));
		command_pretty_dump(root->cmd, indent * 1.5);
		root = root->next;
	}	
}
