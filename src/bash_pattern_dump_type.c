/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bash_pattern_dump_type.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:56:28 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:56:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bash_pattern.h"

char	*pattern_dump_type(t_bash_pattern_type type)
{
	if (type == P_COMMAND)
		return ("COMMAND");
	if (type == P_PATH)
		return ("PATH");
	if (type == P_ASSIGNMENT)
		return ("ASSIGNMENT");
	if (type == P_NO_TYPE)
		return ("NO_TYPE");
	return (NULL);
}
