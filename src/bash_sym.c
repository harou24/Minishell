#include "bash_sym.h"

#define EXACT TRUE
#define FUZZY FALSE

/*
** Bash symbol matching for lexing:
** The matcher, bash_match(), works as follows:
**   - it reads from a string from left to right and attempts to match token-
**     patterns as specified in g_bash_sym_list[] and returns a t_token_type
**
** It uses the lookup table g_bash_sym_list[] to accomplish this:
**   - an EXACT type must be matched exactly by a call to strcmp()
**   - a FUZZY type can be matched by using any symbol in it's *key in any
**     order and number
*/

static const t_bash_sym	g_bash_sym_list[] = {
	{WORD, FUZZY,		"0123456789abcdefghijklmnopqrstuvwxyz\
						ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
	{SYM, FUZZY,		"@%^(~)-_+]}[{:/?.,&"},
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

t_bool	is_bash_sym_exact(const char *str, size_t len, const t_bash_sym *token)
{
	const size_t	tokenkeylen = ft_strlen(token->key);

	if (tokenkeylen > len)
		len = tokenkeylen;
	return (ft_strncmp(str, token->key, len) == 0);
}

t_bool	is_bash_sym_fuzzy(const char *str, size_t len, const t_bash_sym *token)
{
	size_t	i;

	i = 0;
	while (i < len && str[i] != '\0')
	{
		if (ft_strcount(token->key, str[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	is_bash_sym(const char *str, size_t len, const t_bash_sym *token)
{
	if (token->match_style == EXACT)
		return (is_bash_sym_exact(str, len, token));
	if (token->match_style == FUZZY)
		return (is_bash_sym_fuzzy(str, len, token));
	return (FALSE);
}

t_token_type_e	bash_match(const char *str, size_t len)
{
	const size_t	token_count = sizeof(g_bash_sym_list)
					/ sizeof(g_bash_sym_list[0]);
	t_bash_sym		*candidate;
	size_t			i;

	i = 0;
	candidate = NULL;
	while (i < token_count)
	{
		if (is_bash_sym(str, len, &g_bash_sym_list[i]))
		{
			if (candidate == NULL || ft_strlen(g_bash_sym_list[i].key)
				> ft_strlen(candidate->key))
				candidate = (t_bash_sym *)&g_bash_sym_list[i];
		}
		i++;
	}
	if (candidate == NULL)
		return (NO_TYPE);
	else
		return (candidate->type);
}
