#ifndef EXECSCHEME_H
# define EXECSCHEME_H

#include "bash_pattern.h"

typedef enum				t_exec_relation_type
{
	REL_SIMPLE,
	REL_PIPE
}							t_exec_relation_type;

struct						s_execscheme;
typedef struct				s_execscheme
{
	char					*cmd;
	char					**argv;
	int						argc;
	t_bash_pattern_type		op_type; /* t_bash_pattern_type is a quite obscure name like this */
	t_exec_relation_type	relation_type;
	int						(*f)(char *cmd, char **argv, int argc);
	struct s_execscheme		*next;
}							t_execscheme;

t_execscheme				*execscheme_create();
t_execscheme				*execscheme_destroy(t_execscheme **execscheme);

#endif
