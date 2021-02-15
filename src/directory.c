#include "directory.h"

const char	*directory_get_current_dir(void)
{
	char	buffer[BUFFER_SIZE];

	return (getcwd(buffer, sizeof(buffer)));
}
