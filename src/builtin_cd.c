#include "bash_ops.h"
#include "env_access"

/* maybe put this in env_access */
char	*get_parent_dir()
{
	char *current = env_get_current_dir();
	char *parent_dir = ft_substr(current, 0, ft_strrchr(current, '/'));
	return (parent_dir);
}

int	go_to_parent_dir()
{
	char *parent_dir = get_parent_dir();
	int ret = directory_change_dir(parent_dir);
	free(parent_dir);
	return (ret);
}

int 	go_to_prev_dir()
{
	return (directory_change_dir(env_get_prev_dir()));
}

int	go_to_home()
{
	return (directory_change_dir(env_get_home()));
}

int	go_to_path(const char *path)
{
	return (directory_change_dir(path));
}

int	go_to_dots(const char *dots)
{

	int	nb_dots;
	int	count;
	int	ret;

	nb_dots = ft_strlen(dots);
	count = 1;
	if (nb_dots == count)
		return (go_to_path(env_get_current_dir()));
	while (count < nb_dots)
	{
		ret = go_to_parrent_dir();
		if (ret != 0)
			return (ret);
		count++;
	}
	return (ret);
}

int	builtin_cd(t_command *cmd)
{
	if (cmd->argv->argc == 1)
		return(go_to_home());
	else
	{
		if (dots_only(cmd->argv->argv[1]))
	}
	return(directory_change_dir(cmd->argv->argv[1]));
}
