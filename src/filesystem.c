/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filesystem.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:01:34 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:01:35 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "debugger.h"
#include "filesystem.h"

int	fs_open(const char *fname, int flags)
{
	int	fd;

	fd = open(fname, flags);
	if (fd == -1)
	{
		dbg("File %s failed to open! errno: %s\n", fname, strerror(errno));
	}
	return (fd);
}

t_bool	fs_exists(const char *fname)
{
	struct stat	buffer;

	return (stat(fname, &buffer) == 0);
}

t_bool	fs_has_type(const char *fname, t_filetype ftype)
{
	struct stat	buffer;

	return (stat(fname, &buffer) == 0 && (buffer.st_mode & S_IFMT) == ftype);
}

t_bool	fs_has_mode(const char *fname, t_filemode fmode)
{
	struct stat	buffer;

	return (stat(fname, &buffer) == 0 && (buffer.st_mode & fmode));
}
