#include "prompt.h"

int main(void)
{
	t_prompt *prompt = prompt_create("user", "host");
	prompt_print(prompt);
	prompt_destroy(prompt);
	return (0);
}
