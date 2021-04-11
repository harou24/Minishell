#ifndef EXECSCHEME_H
# define EXECSCHEME_H

#include "token.h"
#include "command.h"

typedef enum				e_exec_relation_type
{
	REL_START =		1<<1,
	REL_SEQ =		1<<2,
	REL_PIPE =		1<<3,
	REL_READ =		1<<4,
	REL_APPEND =	1<<5,
	REL_WRITE =		1<<6,
	REL_END =		1<<7,
	REL_NO_TYPE =	1<<8,
	REL_TAB_SIZE
}							t_exec_relation_type;

typedef enum				e_exec_op_type
{
	OP_COMMAND,
	OP_PATH,
	OP_ASSIGNMENT,
	OP_BUILTIN_ECHO,
	OP_BUILTIN_CD,
	OP_BUILTIN_PWD,
	OP_BUILTIN_EXPORT,
	OP_BUILTIN_UNSET,
	OP_BUILTIN_ENV,
	OP_BUILTIN_EXIT,
	OP_NO_TYPE,
	OP_TAB_SIZE
}							t_exec_op_type;

/* accessor symbols for rel_type[2] in t_execscheme*/
#define PREV_R				0
#define NEXT_R				1

struct						s_execscheme;
typedef struct				s_execscheme
{
	t_exec_op_type			op_type;
	t_exec_relation_type	rel_type[2];
	int						pipe[2];
	pid_t					pid;
	t_command				*cmd;
	struct s_execscheme		*prev;
	struct s_execscheme		*next;
}							t_execscheme;

void						execscheme_attach(t_execscheme *root, t_execscheme *scheme);

t_execscheme				*execscheme_create();
t_execscheme				*execscheme_destroy(t_execscheme **execscheme);

t_exec_relation_type		execscheme_get_relation_type_for_token(t_token *token);
t_exec_op_type				execscheme_get_op_type_for_token(t_token *token);

const char					*execscheme_dump_op_type(t_exec_op_type type);
const char					*execscheme_dump_relation_type(t_exec_relation_type type);

void						execscheme_pretty_dump(t_execscheme *root, int indent);
#endif
