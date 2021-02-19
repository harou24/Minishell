#ifndef EXECSCHEME_H
# define EXECSCHEME_H

typedef enum				e_exec_relation_type
{
	REL_SIMPLE,
	REL_PIPE
}							e_exec_relation_type;

struct						s_execscheme;
typedef struct				s_execscheme
{
	char					*cmd;
	char					**argv;
	int						argc;
	e_exec_relation_type	relation_type;
	struct s_execscheme		*next;
}							t_execscheme;

t_execscheme				*execscheme_create();

t_execscheme				*execscheme_destroy(t_execscheme **execscheme);

#endif
