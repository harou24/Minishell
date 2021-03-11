#include <assert.h>
#include <stdlib.h>

#include "env_singleton.h"
#include "filesystem.h"

#include "path.h"

static char *__fullpath(const char *dir, const char *name)
{
	char *fullpath;

	fullpath = ft_strjoin_multi(3, dir, "/", name); /* this could be very unsafe*/
	if (!fs_exists(fullpath))
	{
		free(fullpath);
		fullpath = NULL;
	}
	return (fullpath);
}


t_bool	path_contains(const char *path, const char *name)
{
	char	*fullpath;

	if ((fullpath = path_expand(path, name)))
	{
		free(fullpath);
		return (TRUE);
	}
	return (FALSE);
}

char	*path_expand(const char *path, const char *name)
{
	char	*dir;
	char	*fullpath;

	dir = ft_strtok((char *)path, ":");
	while (dir)
	{
		if ((fullpath = __fullpath(dir, name)))
		{
			free(dir);
			return (fullpath);
		}
		free(dir);
		dir = ft_strtok(NULL, ":");
	}
	return (NULL);
}
