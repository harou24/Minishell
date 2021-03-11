#include <sys/stat.h>

#include "filesystem.h"

t_bool	file_exists (const char *filename)
{
 	struct stat	buffer;
	
 	return (stat(filename, &buffer) == 0 && S_ISREG(buffer.st_mode));
}

t_bool	file_is_executable(const char *filename)
{
	struct stat	buffer;
	
 	return (stat(filename, &buffer) == 0
			&& S_ISREG(buffer.st_mode)
			&& buffer.st_mode & S_IXUSR);
}
