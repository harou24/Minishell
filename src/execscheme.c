#include <assert.h>
#include <stdlib.h>
#include "libft.h"

#include "journal.h"
#include "execscheme.h"

static const t_exec_relation_type g_reltok_tab__[TOKEN_TYPE_SIZE] =	{
					[WORD] = REL_SIMPLE,
					[STRING] = REL_SIMPLE,
					[LITERAL] = REL_SIMPLE,
					[ASSIGNMENT] = REL_SIMPLE,
					[ESCAPE] = REL_SIMPLE,
					[VARIABLE] = REL_SIMPLE,
					[SPACE] = REL_SIMPLE,
					[PIPE] = REL_PIPE,
					[NEWLINE] = REL_SIMPLE,
					[SEMICOLON] = REL_SIMPLE,
					[OP_READ] = REL_READ,
					[OP_APPEND] = REL_APPEND,
					[OP_WRITE] = REL_WRITE,
					[NULLBYTE] = REL_SIMPLE,
					[NO_TYPE] = REL_NO_TYPE
				};

typedef struct 				s_optok__
{
	const t_exec_op_type	type;
	const char				*key;
}							t_optok__;

static const t_optok__ g_optok_tab__[] = {
					{ OP_BUILTIN_ECHO, "echo" },
					{ OP_BUILTIN_CD, "cd" },
					{ OP_BUILTIN_PWD, "pwd" },
					{ OP_BUILTIN_EXPORT, "export" }, 
					{ OP_BUILTIN_UNSET, "unset" },
					{ OP_BUILTIN_ENV, "env" },
					{ OP_BUILTIN_EXIT, "exit"}
				};

void			execscheme_attach(t_execscheme *root, t_execscheme *scheme)
{
	assert(root);
	assert(scheme);

	while (root->next)
		root = root->next;
	root->next = scheme;
}

t_exec_relation_type execscheme_get_relation_type_for_token(t_token *token)
{
	if (!token || token->type == NULLBYTE)
		return (REL_END);
	return (g_reltok_tab__[token->type]);
}

t_exec_op_type		execscheme_get_op_type_for_token(t_token *token)
{
	const size_t	tabsize = sizeof(g_optok_tab__)/sizeof(g_optok_tab__[0]);
	char			*key;
	size_t			i;

	assert(token);
	i = 0;
	while (i < tabsize)
	{
		key = journal_get_string_for_token(token);
		assert(key);
		if (ft_strcmp(key, g_optok_tab__[i].key) == 0)
		{
			free(key);
			return (g_optok_tab__[i].type);
		}
		free(key);
		i++;
	}
	return (OP_COMMAND); /* assume any non-matched word is a command */
}

t_execscheme	*execscheme_create()
{
	t_execscheme *scheme;

	scheme = ft_calloc(sizeof(t_execscheme), 1);
	if (scheme)
	{

	}
	return (scheme);
}

#include <stdio.h>

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

const char		*execscheme_dump_op_type(t_exec_op_type type)
{
	switch (type)
	{
		case OP_COMMAND:
			return ("OP_COMMAND");
		case OP_PATH:
			return ("PATH");
		case OP_ASSIGNMENT:
			return ("OP_ASSIGNMENT");
		case OP_BUILTIN_ECHO:
			return ("OP_BUILTIN_ECHO");
		case OP_BUILTIN_CD:
			return ("OP_BUILTIN_CD");
		case OP_BUILTIN_PWD:
			return ("OP_BUILTIN_PWD");
		case OP_BUILTIN_EXPORT:
			return ("OP_BUILTIN_EXPORT");
		case OP_BUILTIN_UNSET:
			return ("OP_BUILTIN_UNSET");
		case OP_BUILTIN_ENV:
			return ("OP_BUILTIN_ENV");
		case OP_BUILTIN_EXIT:
			return ("OP_BUILTIN_EXIT");
		default:
			return ("NO_TYPE");
	}
}

const char		*execscheme_dump_relation_type(t_exec_relation_type type)
{
	switch (type)
	{
		case REL_SIMPLE:
			return ("REL_SIMPLE");
		case REL_PIPE:
			return ("REL_PIPE");
		case REL_READ:
			return ("REL_READ");
		case REL_APPEND:
			return ("REL_APPEND");
		case REL_WRITE:
			return ("REL_WRITE");
		case REL_END:
			return ("REL_END");
		default:
			return ("NO_TYPE");
	}
}

void			execscheme_pretty_dump(t_execscheme *root, int indent)
{
	assert(root);
	
	while (root)
	{
		printf("%*s :\n", indent, "Scheme");
		printf("%*s : %s\n", (int)(indent * 1.5), "OP", execscheme_dump_op_type(root->op_type));
		printf("%*s : %s\n", (int)(indent * 1.5), "REL", execscheme_dump_relation_type(root->relation_type));
		command_pretty_dump(root->cmd, indent * 1.5);
		root = root->next;
	}	
}
