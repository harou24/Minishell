#include "bash_ops.h"
#include "env_access.h"
#include "filesystem_traversal.h"
#include "filesystem.h"
#include "ft_printf.h"
#include "path.h"

t_bool	__update_dir_change(char *new_path)
{
	return (env_set_s("OLDPWD", env_get_s("PWD"), SCOPE_ENVIRON)
		&& env_set_s("PWD", new_path, SCOPE_ENVIRON));
}

t_bool	__is_tilde(const char *str)
{
	return (ft_strcmp(str, "~") == 0);
}

t_bool	__is_dash(const char *str)
{
	return (ft_strcmp(str, "-") == 0);
}

t_bool	__is_path_in_cdpath(const char *path)
{
	char	*cdpath;
	char	*dir_name;

	cdpath = env_get_s("CDPATH");
	if (!cdpath)
		return (FALSE);
	dir_name = ft_strrchr(cdpath, '/');
	if (dir_name && dir_name + 1)
		return ((ft_strcmp(dir_name + 1, path) == 0)
			&& path_contains(cdpath, path));
	return (FALSE);
}

t_bool	__is_print_path_needed(const char *path)
{
	return (__is_dash(path) || __is_path_in_cdpath(path));
}
