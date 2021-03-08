#include "prompt_singleton.h"

static t_prompt *g_prompt__;

static void	__prompt_init()
{
	if (!g_prompt__)
		prompt_init();
}

t_prompt	*prompt_init()
{
	if (g_prompt__)
		return (g_prompt__);
	g_prompt__ = prompt_create("a", "b"); /* need singleton access to env */
	return (g_prompt__);
}

void		prompt_deinit()
{
	if (g_prompt__)
		prompt_destroy(g_prompt__);
}

char		*prompt()
{
	__prompt_init();
	prompt_print(g_prompt__);
	return (prompt_read());
}
