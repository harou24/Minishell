#include <assert.h>
#include "journal.h"

#define V_DEF_SIZE 128

extern t_journal	*g_journal__;

t_journal	*journal_create(void)
{
	if (g_journal__)
		return (g_journal__);
	g_journal__ = ft_calloc(sizeof(t_journal), 1);
	if (g_journal__)
	{
		g_journal__->counter = ft_calloc(
				sizeof(t_journal_storetype), TOKEN_TYPE_SIZE);
		if (!g_journal__->counter
			|| !vector(&g_journal__->tokens, V_CREATE, V_DEF_SIZE, NULL))
			return (journal_destroy(&g_journal__));
	}
	return (g_journal__);
}

void	journal_set_input_str(char *str)
{
	journal_clear_input_str();
	g_journal__->str = ft_strdup(str);
}

char	*journal_get_input_str(void)
{
	return (g_journal__->str);
}
