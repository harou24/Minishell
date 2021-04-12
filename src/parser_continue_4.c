#include <assert.h>

#include "debugger.h"
#include "parser.h"

extern t_parser	*g_parser__;

t_bool	parse_is_variable(t_token *var_name)
{
	assert(var_name);
	return (var_name && (var_name->type == WORD || var_name->type == SYM || var_name->type == ASSIGNMENT || var_name->type == VARIABLE));
}

t_bool	parse_expand_first_variable(t_vector tokens, t_token *var_sym)
{
	const size_t	var_sym_index = var_sym->index;
	t_token			*var_name;

	var_name = journal_get(var_sym_index + 1);
	if (!parse_is_variable(var_name))
	{
		var_sym->type = WORD;
		journal_rebuild_tokens();
		return (TRUE);
	}
	parse_perform_var_substitution(tokens, var_sym, var_name);
	return (TRUE);
}

t_bool	parse_expand_variables(void)
{
	t_vector	*tokens;

	if (journal_has_tokentype(VARIABLE) == 0)
		return (TRUE);
	tokens = journal_get_token_vector();
	while (journal_has_tokentype(VARIABLE) > 0)
	{
		assert(journal_find_nth_type(VARIABLE, 0));
		if (journal_find_nth_type(VARIABLE, 0)->index
			>= g_parser__->matcharea.end)
			break ;
		parse_expand_first_variable(tokens, journal_find_nth_type(VARIABLE, 0));
	}
	return (TRUE);
}

t_bool	parse_should_expand_literals(void)
{
	t_token		*string;
	t_token		*literal;

	string = journal_find_nth_type(STRING, 0);
	literal = journal_find_nth_type(LITERAL, 0);
	return (!string || (string && literal && string->index > literal->index));
}

t_bool	parse_expand(void)
{
	size_t	jsize;

	jsize = journal_size();
	if (parse_should_expand_literals())
	{
		if (!parse_expand_strings(LITERAL))
			return (FALSE);
	}
	if (!parse_expand_variables())
		return (FALSE);
	if (!parse_expand_strings(STRING))
		return (FALSE);
	g_parser__->matcharea.end -= jsize - journal_size();
	return (TRUE);
}
