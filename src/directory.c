#include <stdlib.h>
#include <errno.h>

#include <dirent.h>
#include <unistd.h>

#include "libft.h"

#include "filesystem.h"

char	*directory_get_current_dir(void)
{
	char	*buffer = (char *)malloc(PATH_MAX);

	if (getcwd(buffer, PATH_MAX))
		return(buffer);
	/* handle longer directory names */
	free(buffer);
	return (NULL);
}

int		directory_change_dir(const char *path)
{
	if (chdir(path) == 0)
		return (0);
	return (errno);
}

t_bool	directory_exists(const char *path)
{
	DIR*	dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (TRUE);
	}
	return (FALSE);
}
