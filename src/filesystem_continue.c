#include "filesystem.h"

t_bool	file_is_executable(const char *fname)
{
	return (fs_has_type(fname, F_REG) && fs_has_mode(fname, FM_EXEC));
}

t_bool	file_is_readable(const char *fname)
{
	return (fs_has_type(fname, F_REG) && fs_has_mode(fname, FM_READ));
}

t_bool	file_is_writeable(const char *fname)
{
	return (fs_has_type(fname, F_REG) && fs_has_mode(fname, FM_WRITE));
}

t_bool	directory_exists(const char *dname)
{
	return (fs_has_type(dname, F_DIR));
}

t_bool	directory_is_openable(const char *dname)
{
	return (fs_has_type(dname, F_DIR) && fs_has_mode(dname, FM_EXEC | FM_READ));
}
