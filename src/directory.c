#include "directory.h"

char	*directory_get_current_dir(void)
{
	char buffer[255];
	return (getcwd(buffer, sizeof(buffer)));
}
