#include "env.h"
#include "libft.h"

int	main(int argc, char **argv, char **_env)
{
	(void)argc;
	(void)argv;
	t_env *env = env_create((const char **)_env);
	env_print_out(env, STDERR);
	env_destroy(env);
	return (0);
}
