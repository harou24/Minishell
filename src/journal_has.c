#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

int	journal_has_token(const t_token *token)
{
	return (journal_has_tokentype(token->type));
}

int	journal_has_tokentype(const e_token_type type)
{
	return (g_journal__->counter[type]);
}
