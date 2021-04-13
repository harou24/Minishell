/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realpath.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:02:01 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:02:03 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bash_ops.h"
#include <limits.h>
#include <stdlib.h>

char	*ft_realpath(char *path)
{
	char	resolved_path[1024];

	realpath(path, resolved_path);
	return (ft_strdup(resolved_path));
}
