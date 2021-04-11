#include "execscheme.h"
#include "debugger.h"

const char	*execscheme_dump_op_type(t_exec_op_type type)
{
	if (type == OP_COMMAND)
		return ("OP_COMMAND");
	if (type == OP_PATH)
		return ("PATH");
	if (type == OP_ASSIGNMENT)
		return ("OP_ASSIGNMENT");
	if (type == OP_BUILTIN_ECHO)
		return ("OP_BUILTIN_ECHO");
	if (type == OP_BUILTIN_CD)
		return ("OP_BUILTIN_CD");
	if (type == OP_BUILTIN_PWD)
		return ("OP_BUILTIN_PWD");
	if (type == OP_BUILTIN_EXPORT)
		return ("OP_BUILTIN_EXPORT");
	if (type == OP_BUILTIN_UNSET)
		return ("OP_BUILTIN_UNSET");
	if (type == OP_BUILTIN_ENV)
		return ("OP_BUILTIN_ENV");
	if (type == OP_BUILTIN_EXIT)
		return ("OP_BUILTIN_EXIT");
	return ("NO_TYPE");
}

const char	*execscheme_dump_relation_type(t_exec_relation_type type)
{
	if (type == REL_START)
		return ("REL_START");
	if (type == REL_SEQ)
		return ("REL_SEQ");
	if (type == REL_PIPE)
		return ("REL_PIPE");
	if (type == REL_READ)
		return ("REL_READ");
	if (type == REL_APPEND)
		return ("REL_APPEND");
	if (type == REL_WRITE)
		return ("REL_WRITE");
	if (type == REL_END)
		return ("REL_END");
	return ("NO_TYPE");
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
