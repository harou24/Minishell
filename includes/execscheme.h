#ifndef EXECSCHEME_H
# define EXECSCHEME_H

#include "command.h"

typedef enum				e_exec_relation_type
{
	REL_SIMPLE,
	REL_PIPE
}							t_exec_relation_type;

typedef enum				e_exec_op_type
{
	E_COMMAND,
	E_ASSIGNMENT,
	E_BUILTIN_ECHO
}							t_exec_op_type;

struct						s_execscheme;
typedef struct				s_execscheme
{
	t_exec_op_type			op_type;
	t_exec_relation_type	relation_type;
	t_command				*cmd;
	struct s_execscheme		*next;
}							t_execscheme;

void						execscheme_attach(t_execscheme *root, t_execscheme *scheme);

t_execscheme				*execscheme_create();
t_execscheme				*execscheme_destroy(t_execscheme **execscheme);

#endif
