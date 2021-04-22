/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection_std_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:05:29 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:05:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include "debugger.h"
#include "filesystem.h"
#include "ft_unistd.h"

#include "libft.h"

static int	g_fd__[2];

void	redir_std_push(void)
{
	g_fd__[STDIN] = dup(STDIN);
	g_fd__[STDOUT] = dup(STDOUT);
}

void	redir_std_pop(void)
{
	dup2(g_fd__[STDIN], STDIN);
	dup2(g_fd__[STDOUT], STDOUT);
}
