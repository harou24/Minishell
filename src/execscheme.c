#include <stdlib.h>
#include "libft.h"
#include "debugger.h"

#include "journal.h"
#include "execscheme.h"

static const t_exec_relation_type	g_reltok_tab__[TOKEN_TYPE_SIZE] = {
					[WORD] = REL_SEQ,
					[STRING] = REL_SEQ,
					[LITERAL] = REL_SEQ,
					[ASSIGNMENT] = REL_SEQ,
					[ESCAPE] = REL_SEQ,
					[VARIABLE] = REL_SEQ,
					[SPACE] = REL_SEQ,
					[PIPE] = REL_PIPE,
					[NEWLINE] = REL_SEQ,
					[SEMICOLON] = REL_SEQ,
					[OP_READ] = REL_READ,
					[OP_APPEND] = REL_APPEND,
					[OP_WRITE] = REL_WRITE,
					[NULLBYTE] = REL_SEQ,
					[NO_TYPE] = REL_NO_TYPE
				};

typedef struct s_optok__
{
	const t_exec_op_type	type;
	const char				*key;
}							t_optok__;

static const t_optok__				g_optok_tab__[] = {
					{OP_BUILTIN_ECHO, "echo"},
					{OP_BUILTIN_CD, "cd"},
					{OP_BUILTIN_PWD, "pwd"},
					{OP_BUILTIN_EXPORT, "export"},
					{OP_BUILTIN_UNSET, "unset"},
					{OP_BUILTIN_ENV, "env"},
					{OP_BUILTIN_EXIT, "exit"}
				};

void	execscheme_attach(t_execscheme *root, t_execscheme *scheme)
{
	while (root->next)
		root = root->next;
	root->next = scheme;
	scheme->prev = root;
	scheme->rel_type[PREV_R] = scheme->prev->rel_type[NEXT_R];
}

t_exec_relation_type	execscheme_get_relation_type_for_token(t_token *token)
{
	if (!token || token->type == NULLBYTE)
		return (REL_END);
	return (g_reltok_tab__[token->type]);
}

t_exec_op_type	execscheme_get_op_type_for_token(t_token *token)
{
	const size_t	tabsize = sizeof(g_optok_tab__) / sizeof(g_optok_tab__[0]);
	char			*key;
	size_t			i;

	i = 0;
	while (i < tabsize)
	{
		key = journal_get_string_for_token(token);
		if (ft_strcmp(key, g_optok_tab__[i].key) == 0)
		{
			free(key);
			return (g_optok_tab__[i].type);
		}
		free(key);
		i++;
	}
	return (OP_COMMAND);
}

t_execscheme	*execscheme_create(void)
{
	t_execscheme	*scheme;

	scheme = ft_calloc(sizeof(t_execscheme), 1);
	if (scheme)
	{
		scheme->pipe[STDIN] = -1;
		scheme->pipe[STDOUT] = -1;
	}
	return (scheme);
}

t_execscheme	*execscheme_destroy(t_execscheme **execscheme)
{
	if (!execscheme)
		return (NULL);
	if (*execscheme)
	{
		execscheme_destroy(&(*execscheme)->next);
		command_destroy(&(*execscheme)->cmd);
		free(*execscheme);
	}
	return ((*execscheme = NULL));
}

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
