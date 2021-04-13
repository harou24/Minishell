/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filesystem_directory.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:01:39 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:01:41 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filesystem.h"

t_bool	directory_exists(const char *dname)
{
	return (fs_has_type(dname, F_DIR));
}

t_bool	directory_is_openable(const char *dname)
{
	return (fs_has_type(dname, F_DIR) && fs_has_mode(dname, FM_EXEC | FM_READ));
}
