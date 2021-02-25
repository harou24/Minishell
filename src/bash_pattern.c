#include <stdlib.h>
#include "bash_pattern.h"

static const t_bash_pattern bash_pat_list[] =	{
													{ P_COMMAND, {WORD, SPACE}, {WORD, SPACE} },
													{ P_ASSIGNMENT, {WORD, SPACE, ASSIGNMENT, WORD}, {} }
												};

t_bash_pattern_type		batch_match_pattern(t_journal *journal, size_t start, size_t len)
{
	/* stub */
	(void)journal;
	(void)start;
	(void)len;
	(void)bash_pat_list;
	return (P_NO_TYPE);
}
