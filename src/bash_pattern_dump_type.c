#include "bash_pattern.h"

char	*pattern_dump_type(t_bash_pattern_type type)
{
	if (type == P_COMMAND)
		return ("COMMAND");
	if (type == P_PATH)
		return ("PATH");
	if (type == P_ASSIGNMENT)
		return ("ASSIGNMENT");
	if (type == P_NO_TYPE)
		return ("NO_TYPE");
	return (NULL);
}
