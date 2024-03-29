/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt_singleton.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:04:39 by sverschu      #+#    #+#                 */
/*   Updated: 2021/05/11 20:35:15 by haachtch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "libprintf.h"
#include "env_access.h"
#include "prompt_singleton.h"

static t_prompt	*g_prompt__ = NULL;

static void	__prompt_init(void)
{
	if (!g_prompt__)
		prompt_init();
}

t_prompt	*prompt_init(void)
{
	if (g_prompt__)
		return (g_prompt__);
	g_prompt__ = prompt_create(env_get_user(), env_get_host());
	return (g_prompt__);
}

void	prompt_deinit(t_prompt **prompt)
{
	if (g_prompt__)
	{
		prompt_destroy(g_prompt__);
		g_prompt__ = NULL;
	}
	if (prompt)
		*prompt = NULL;
}

char	*prompt(int last_error)
{
	char	*cmd;

	__prompt_init();
	prompt_set_error_code(g_prompt__, last_error);
	prompt_update(g_prompt__);
	prompt_print(g_prompt__);
	cmd = prompt_read(g_prompt__);
	if (cmd && ft_strlen(cmd) > 0)
		prompt_add_cmd_to_history(g_prompt__, ft_strdup(cmd));
	return (cmd);
}

t_prompt	*prompt_get(void)
{
	return (g_prompt__);
}
