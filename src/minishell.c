#include "minishell.h"
#include "prompt.h"

int	main(void)
{
	void *prompt = new_prompt("user@42 >\n");
	print_prompt(prompt);
	set_prompt(prompt, "hello_world@42 >\n");
	print_prompt(prompt);
	return (0);
}
