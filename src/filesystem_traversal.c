#include <stdlib.h>
#include <errno.h>

#include <dirent.h>
#include <unistd.h>

#include "libft.h"

#include "filesystem_traversal.h"

static	char	*__get_cur_dir_name(size_t buflen)
{
	char	*buf;

	buf = (char *)malloc(buflen);
	if (!getcwd(buf, buflen))
	{
		free(buf);
		return (NULL);
	}
	return (buf);
}

char	*fs_get_cur_dir_name(void)
{
	char	*buf;
	size_t	buflen;

	buflen = PATH_DEF;
	buf = __get_cur_dir_name(buflen);
	while (!buf
		&& errno == ERANGE
		&& buflen < PATH_MAX)
	{
		buflen *= 2;
		buf = __get_cur_dir_name(buflen);
	}
	return (buf);
}

int	fs_change_dir(const char *dname)
{
	if (chdir(dname) == 0)
		return (0);
	return (errno);
}
