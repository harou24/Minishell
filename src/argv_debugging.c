/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argv_debugging.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:56:10 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:56:17 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "libft.h"
#include "debugger.h"

#include "argv.h"

void	argv_pretty_dump(t_argv *argv, int indent)
{
	size_t	i;

	assert(argv);
	if (argv_get_size(argv) == 0)
		return ;
	dbg("%*s: %i\n", indent, "Argc ", argv_get_size(argv));
	dbg("%*s: \n", indent, "Argv ");
	i = 0;
	while (i < argv_get_size(argv))
	{
		dbg("%*s[%i] : %s\n", (int)(indent) - 2, "", i, argv_get(argv, i));
		i++;
	}
}
