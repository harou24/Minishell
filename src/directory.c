#include "directory.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

#define __DIR_BUFF_SIZE 1024

char	*directory_get_current_dir(void)
{
	char	*buffer = ft_calloc(sizeof(char), __DIR_BUFF_SIZE);

	if (getcwd(buffer, __DIR_BUFF_SIZE))
		return(buffer);
	free(buffer);
	return (NULL);
}
