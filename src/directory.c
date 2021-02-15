#include "directory.h"

#define __DIR_BUFF_SIZE 255

const char	*directory_get_current_dir(void)
{
	char	buffer[__DIR_BUFF_SIZE];

	return (getcwd(buffer, sizeof(buffer)));
}
