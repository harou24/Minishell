#include "assert.h"
#include "bash_sym.h"

#define EXACT TRUE
#define FUZZY FALSE

/*
** Bash symbol matching for lexing:
** The matcher, bash_match(), works as follows:
**   - it reads from a string from left to right and attempts to match token-
**     patterns as specified in bash_sym_list[] and returns a t_token_type
**
** It uses the lookup table bash_sym_list[] to accomplish this:
**   - an EXACT type must be matched exactly by a call to strcmp()
**   - a FUZZY type can be matched by using any symbol in it's *key in any
**     order and number
*/

static const t_bash_sym bash_sym_list[] =	{
													{WORD, FUZZY,		"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ@%^()-_+]}[{:/?.,&"},
													{LITERAL, EXACT,	"\'"},
													{STRING, EXACT,		"\""},
													{ASSIGNMENT, EXACT,	"="},
													{ESCAPE, EXACT,		"\\"},
													{VARIABLE, EXACT,	"$"},
													{SPACE, FUZZY,		" \a\b\r\t\f\v"},
													{PIPE, EXACT,		"|"},
													{NEWLINE, EXACT,	"\n"},
													{SEMICOLON, EXACT,	";"},
													{OP_READ, EXACT,	"<"},
													{OP_APPEND, EXACT,	">>"},
													{OP_WRITE, EXACT,	">"}
												};

t_bool		is_bash_sym_exact(const char *str, size_t len, const t_bash_sym *token)
{
	/* this could be done staticly */
	const size_t tokenkeylen = ft_strlen(token->key);

	if (tokenkeylen > len)
		len = tokenkeylen;
	return (ft_strncmp(str, token->key, len) == 0);
}

t_bool		is_bash_sym_fuzzy(const char *str, size_t len, const t_bash_sym *token)
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

t_bool		is_bash_sym(const char *str, size_t len, const t_bash_sym *token)
{
	/* this doesnt follow open/closed principles */

	if (token->match_style == EXACT)
		return (is_bash_sym_exact(str, len, token));
	if (token->match_style == FUZZY)
		return (is_bash_sym_fuzzy(str, len, token));
	return (FALSE);
}

e_token_type	bash_match(const char *str, size_t len)
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
			if (candidate == NULL || ft_strlen(bash_sym_list[i].key) > ft_strlen(candidate->key)) /* assume longer matches are more accurate */
				candidate = (t_bash_sym *)&bash_sym_list[i];
		}
		i++;
	}
	return ((candidate == NULL) ? NO_TYPE : candidate->type);
}
