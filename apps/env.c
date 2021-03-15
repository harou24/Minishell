#include "env.h"
#include <stdio.h>
#include <stdlib.h>

void print_str_array(const char **arr, int size_arr)
{
printf("\n\n\nHELLO TEST ENV ********\n\n\n");
	int count = 0;
	while(count < size_arr)
	{
		printf("%s\n",arr[count]);
		count++;
	}
}

int main(int argc, char **argv, char **_env)
{
	(void)argv;
	(void)argc;
	t_env *env = env_create((const char **)_env);
	char **env_array = env_to_array(env, ENV);
	print_str_array((const char **)env_array, 10);
	free(env_array);
	env_destroy(env);
	return (0);
}
