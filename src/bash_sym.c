#include "assert.h"
#include "bash_sym.h"

#define EXACT TRUE
#define FUZZY FALSE

static const t_bash_sym bash_sym_list[] =	{
													{WORD, FUZZY,		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@%^()-_+=\\]}[{:/?.,<>"},
													{STRING, EXACT,		"\""},
													{VARIABLE, EXACT,	"$"},
													{SPACE, EXACT,		" "},
													{PIPE, EXACT,		"|"},
													{NEWLINE, EXACT,	"\n"}
												};

t_bool		is_bash_sym_exact(char *str, size_t len, const t_bash_sym *token)
{
	return (ft_strncmp(str, token->key, len) == 0);
}

t_bool		is_bash_sym_fuzzy(char *str, size_t len, const t_bash_sym *token)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		if (ft_strcount(token->key, str[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool		is_bash_sym(char *str, size_t len, const t_bash_sym *token)
{
	/* this doesnt follow open/closed principles */

	if (token->style == EXACT)
		return (is_bash_sym_exact(str, len, token));
	if (token->style == FUZZY)
		return (is_bash_sym_fuzzy(str, len, token));
	return (FALSE);
}

e_token_type	bash_match(char *str, size_t len)
{
	size_t i;
	/* const int token_count = 6; // sizeof ? */
	const size_t token_count = sizeof(bash_sym_list)/sizeof(bash_sym_list[0]);
	assert(token_count == 6);

	i = 0;
	while(i < token_count)
	{
		if (is_bash_sym(str, len, &bash_sym_list[i]))
			return (bash_sym_list[i].type);
		i++;
	}
	return (NO_TYPE);
}
