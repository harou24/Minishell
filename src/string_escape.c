#include <stdlib.h>

#include "string_processing.h"

/*
static const g_escape_tab[128] =	{
										[a] = '\a',
										[b] = '\b',
										[t] = '\t',
										[n] = '\n',
										[v] = '\v',
										[f] = '\f',
										[r] = '\r'
									};

char *get_escaped_char_for_char(char c)
{
	if (g_escape_tab[c] != 0)
		return (g_escape_tab[c])
	else
		return (c);
}
*/

size_t	len_of_escape_chars(const char *str)
{
	size_t	len;

	len = 0;
	while (str && *str == '\\')
	{
		len++;
		str++;
	}
	return (len);
}

size_t	len_until_escape_char(const char *str)
{
	return (ft_strchr(str, '\\') - str);
}

char *extract_escape_chars(const char **str, char *nstr)
{
	size_t	len;

	len = len_of_escape_chars(*str);
	if (len % 2 == 0)
		nstr = ft_strjoin_noreuse(nstr, ft_strsub(*str, 0, len / 2));
	else
		nstr = ft_strjoin_noreuse(nstr, ft_strsub(*str, 0, (len - 1) / 2));
	*str = (char *)(*str + len);
	return (nstr);
}

char	*string_replace_escaped_chars(const char *str)
{
	char	*nstr;
	size_t	len;

	if (ft_strcount(str, '\\') == 0)
		return (ft_strdup(str));
	nstr = NULL;
	while (str && *str)
	{
		len = len_until_escape_char(str);
		nstr = ft_strjoin_noreuse(nstr, ft_strsub(str, 0, len));
		str += len;
		if (str && *str == '\\')
			nstr = extract_escape_chars(&str, nstr);
	}
	return (nstr);
}

t_bool	string_replace_escaped_chars_inline(char *str)
{
	char	*tmpstr;

	if (ft_strcount(str, '\\') == 0)
		return (TRUE);
	tmpstr = string_replace_escaped_chars(str);
	if (tmpstr)
	{
		ft_strlcpy(str, tmpstr, ft_strlen(str));
		free(tmpstr);
		return (TRUE);
	}
	return (FALSE);
}
