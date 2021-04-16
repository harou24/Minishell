/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execscheme.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:59:44 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:59:45 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "debugger.h"

#include "process.h"
#include "journal.h"
#include "execscheme.h"

static const t_exec_relation_type	g_relation_tab__[TOKEN_TYPE_SIZE] = {
					[PIPE] = REL_PIPE,
					[SEMICOLON] = REL_SEQ,
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
	if (token->type >= TOKEN_TYPE_SIZE)
	{
		errno = ERANGE;
		return (REL_NO_TYPE);
	}
	if (!token || token->type == NULLBYTE)
		return (REL_END);
	return (g_relation_tab__[token->type]);
}

t_exec_op_type	execscheme_get_op_type_for_token(t_token *token)
{
	const size_t	tabsize = sizeof(g_optok_tab__) / sizeof(g_optok_tab__[0]);
	char			*key;
	size_t			i;

	if (token_is_valid_argument(journal_get(token->index + 1)))
		return (OP_COMMAND);
	key = journal_get_string_for_token(token);
	i = 0;
	while (i < tabsize)
	{
		if (ft_strcmp(key, g_optok_tab__[i].key) == 0)
		{
			free(key);
			return (g_optok_tab__[i].type);
		}
		i++;
	}
	free(key);
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
		scheme->redir = redir_create();
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
		if ((*execscheme)->pid > 0)
			p_signal((*execscheme)->pid, SIGTERM);
		redir_destroy(&(*execscheme)->redir);
		free(*execscheme);
	}
	return ((*execscheme = NULL));
}
