#include "ft_printf.h"
#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	int r_value;

	if (argc == 1)
	{
		shell_interactive(envp);
		shell_deinit();
		return (0);
	}
	else if (argc >= 3 && ft_strcmp(argv[1], "-c") == 0) 
	{
		shell_init(envp);
		r_value = shell_exec(argv[2]);
		shell_deinit();
		return (r_value);
	}
	else
	{
		ft_dprintf(STDERR, "RTFM\n");
	}
	return (1);
}
