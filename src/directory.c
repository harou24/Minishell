#include "directory.h"

const char	*directory_get_current_dir(void)
{
	char *buffer;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	return (getcwd(buffer, sizeof(buffer)));
}
