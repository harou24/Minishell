/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filesystem_file.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:01:46 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:01:47 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filesystem.h"

t_bool	file_exists(const char *fname)
{
	return (fs_has_type(fname, F_REG));
}

t_bool	file_is_executable(const char *fname)
{
	return (fs_has_type(fname, F_REG) && fs_has_mode(fname, FM_EXEC));
}

t_bool	file_is_readable(const char *fname)
{
	return (fs_has_type(fname, F_REG) && fs_has_mode(fname, FM_READ));
}

t_bool	file_is_writeable(const char *fname)
{
	return (fs_has_type(fname, F_REG) && fs_has_mode(fname, FM_WRITE));
}
