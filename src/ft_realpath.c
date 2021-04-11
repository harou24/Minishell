#include "bash_ops.h"
#include <limits.h>
#include <stdlib.h>

char	*ft_realpath(char *path)
{
	char	resolved_path[1024];

	realpath(path, resolved_path);
	return (ft_strdup(resolved_path));
}
