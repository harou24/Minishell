#include <assert.h>
#include "journal.h"

extern t_journal	*g_journal__;

t_token	*journal_find_nth_token(const t_token *token, int n)
{
	return (journal_find_nth_type(token->type, n));
}
