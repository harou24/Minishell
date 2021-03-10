#include <assert.h>
#include <stdlib.h>

#include "env_singleton.h"
#include "file.h"
#include "path.h"

static char	**g_path__;

static void		__buildpath()
{
	char		*env_path;
	char		*dir;
	size_t		i;

	if (g_path__)
		return ;
	env_path = env_get_s("PATH");
	assert(env_path);

	g_path__ = (char **)malloc(sizeof(char *) * (ft_strcount(env_path, ':') + 2));
	assert(g_path__);

	dir = ft_strtok(env_path, ":");
	i = 0;
	while (dir)
	{
		g_path__[i++] = dir;
		dir = ft_strtok(NULL, ":");
	}
	g_path__[i] = NULL;
}

static char *match_abspath(const char *execname, const char *dir)
{
	char *abspath;

	abspath = ft_strjoin_multi(3, dir, "/", execname); /* this could be very unsafe*/
	if (!file_is_executable(abspath))
	{
		free(abspath);
		abspath = NULL;
	}
	return (abspath);
}


t_bool	is_in_path(const char *execname)
{
	char	*_abspath;

	__buildpath();
	_abspath = abspath(execname);
	if (_abspath)
	{
		free(_abspath);
		return (TRUE);
	}
	return (FALSE);
}

char	*abspath(const char *execname)
{
	char *_abspath;
	size_t	i;

	__buildpath();
	i = 0;
	while (g_path__[i])
	{
		if ((_abspath = match_abspath(execname, g_path__[i])))
			return (_abspath);
		i++;
	}
	return (NULL);
}
