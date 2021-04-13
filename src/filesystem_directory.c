#include "filesystem.h"

t_bool	directory_exists(const char *dname)
{
	return (fs_has_type(dname, F_DIR));
}

t_bool	directory_is_openable(const char *dname)
{
	return (fs_has_type(dname, F_DIR) && fs_has_mode(dname, FM_EXEC | FM_READ));
}
