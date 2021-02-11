#include "minishell.h"
#include "prompt.h"

int	main(void)
{
	void *prompt = new_prompt("user@42 >");
	print_prompt(prompt);
	return (0);
}
