#include "assert.h"
#include "bash_sym.h"

#define EXACT TRUE
#define FUZZY FALSE

static const t_bash_sym bash_sym_list[] =	{
													{WORD, FUZZY,		"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@%^()-_+=\\]}[{:/?.,&"},
													{STRING, EXACT,		"\""},
													{VARIABLE, EXACT,	"$"},
													{SPACE, FUZZY,		" \a\b\r\n\t\f\v"},
													{PIPE, EXACT,		"|"},
													{NEWLINE, EXACT,	"\n"},
													{SEMICOLON, EXACT,	";"},
													{OP_READ, EXACT,	"<"},
													{OP_APPEND, EXACT,	">>"},
													{OP_WRITE, EXACT,	">"}
												};

t_bool		is_bash_sym_exact(char *str, size_t len, const t_bash_sym *token)
{
	/* this could be done staticly */
	const size_t tokenkeylen = ft_strlen(token->key);

	if (tokenkeylen > len)
		len = tokenkeylen;
	return (ft_strncmp(str, token->key, len) == 0);
}

t_bool		is_bash_sym_fuzzy(char *str, size_t len, const t_bash_sym *token)
{
	size_t i;

	i = 0;
	while (i < len && str[i] != '\0')
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
	const size_t	token_count = sizeof(bash_sym_list)/sizeof(bash_sym_list[0]);
	t_bash_sym		*candidate;
	size_t			i;

	i = 0;
	candidate = NULL;
	while(i < token_count)
	{
		if (is_bash_sym(str, len, &bash_sym_list[i]))
		{
			if (candidate == NULL || ft_strlen(bash_sym_list[i].key) > ft_strlen(candidate->key))
				candidate = (t_bash_sym *)&bash_sym_list[i];
		}
		i++;
	}
	return ((candidate == NULL) ? NO_TYPE : candidate->type);
}
