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
	assert(token);
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

t_execscheme	*execscheme_destroy(t_execscheme **execscheme)
{
	if (!execscheme)
		return (NULL);
	if (*execscheme)
	{
		command_destroy(&(*execscheme)->cmd);
		free(*execscheme);
	}
	return ((*execscheme = NULL));
}
