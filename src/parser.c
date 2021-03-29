#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "debugger.h"
#include "bash_pattern.h"
#include "parser.h"
#include "env_singleton.h"

# define VEC_SIZE 128

static t_parser *g_parser__;

/* helper function for parse_expand_first_string */
t_vector		parse_get_subtokens(t_token *first, t_token *last)
{
	t_vector	subtokens;
	
	assert(first);
	assert(last);

	vector(&subtokens, V_CREATE, VEC_SIZE, NULL);
	if (!subtokens)
		return (NULL);
	while(first->next && first->next != last)
	{
		vector(&subtokens, V_PUSHBACK, 0, first->next);
		first = first->next;
	}
	return (subtokens);	
}

/* helper function for parse_expand_first_string */
void			parse_replace_tokens_with_token(t_vector tokens, t_token *first, t_token *last, t_token *token)
{
	const ssize_t index_of_first = first->index;
	ssize_t index;

	index = last->index;
	assert(index > 0);
	while(index >= index_of_first)
	{
		token_destroy(vector(&tokens, V_POPAT, index, NULL));
		index--;
	}
	assert(vector(&tokens, V_PUSHAT, (index_of_first < (ssize_t)journal_size()) ? (size_t)index_of_first : journal_size(), token));
	assert(journal_size() > 0);
	journal_rebuild_tokens();
}

void			parse_perform_string_substitution(t_vector tokens, t_token *first, t_token *last, t_vector subtokens)
{
	char		*string;
	t_token		*cur_token;
	size_t		index;
	t_token		*token;

	assert(first);
	assert(last);
	assert(tokens);
	assert(subtokens);

	token = token_create(range(first->range.begin, last->range.end), WORD);

	index = 0;
	string = NULL;
	while ((cur_token = vector(&subtokens, V_PEEKAT, index, NULL)))
	{
		string = ft_strjoin_noreuse(string, journal_get_string_for_token(cur_token));
		index++;
	}
	token->string = (string != NULL) ? string : ft_strdup("");
	parse_replace_tokens_with_token(tokens, first, last, token);
}

t_bool			parse_expand_first_string(t_vector tokens, t_token *first, t_token *last)
{
	t_vector subtokens;

	assert(tokens);
	assert(first);
	assert(last);
	assert(first != last);

	subtokens = parse_get_subtokens(first, last);
	assert(subtokens);

	/* stitch everything together */
	parse_perform_string_substitution(tokens, first, last, subtokens);
	
	vector(&subtokens, V_DESTROY, FALSE, NULL);
	return (TRUE);
}

t_bool			parse_expand_strings(e_token_type string_type)
{
	t_vector *tokens;

	if (journal_has_tokentype(string_type) == 0)
		return (TRUE);
	if (!(journal_has_tokentype(string_type) % 2 == 0))
		return (FALSE);
	tokens = journal_get_token_vector();
	while (journal_has_tokentype(string_type) > 0)
		parse_expand_first_string(tokens, journal_find_nth_type(string_type, 0), journal_find_nth_type(string_type, 1));	
	return (TRUE);
}

char			*parse_retreive_var_from_env_for_token(t_token *token)
{
	char *key;
	char *var;

	key = ft_strsub(journal_get_input_str(), token->range.begin, 1 + token->range.end - token->range.begin);
	assert(key);

	var = env_get_s(key);
	var = (var == NULL) ? ft_strdup("") : ft_strdup(var);
	free(key);
	return(var);
}

void			parse_perform_var_substitution(t_vector tokens, t_token *var_sym, t_token *var_name)
{
	t_token *token;
	
	assert(var_sym->index == var_name->index - 1);

	token = token_create(range(var_name->range.begin - 1, var_name->range.end), WORD);
	assert(token);

	token->string = parse_retreive_var_from_env_for_token(var_name);
	assert(token->string);

	parse_replace_tokens_with_token(tokens, var_sym, var_name, token);
}

t_bool			parse_is_variable(t_token *var_name)
{
	return (var_name && var_name->type == WORD);
}

t_bool			parse_expand_first_variable(t_vector tokens, t_token *var_sym)
{
	assert(tokens);
	assert(var_sym);

	const size_t	var_sym_index = var_sym->index;
	t_token			*var_name;

	var_name = journal_get(var_sym_index + 1);
	if (!parse_is_variable(var_name))
	{
		/* this was just a $ sign */
		var_sym->type = WORD;
		journal_rebuild_tokens();
		return (TRUE);
	}
	parse_perform_var_substitution(tokens, var_sym, var_name);
	return (TRUE);
}

t_bool			parse_expand_variables()
{
	t_vector *tokens;

	if (journal_has_tokentype(VARIABLE) == 0)
		return (TRUE);
	tokens = journal_get_token_vector();
	while (journal_has_tokentype(VARIABLE) > 0)
	{
		assert(journal_find_nth_type(VARIABLE, 0));
		parse_expand_first_variable(tokens, journal_find_nth_type(VARIABLE, 0));	
	}
	return (TRUE);
}

t_bool			parse_should_expand_literals()
{
	t_token		*string;
	t_token		*literal;
	
	string = journal_find_nth_type(STRING, 0);
	literal = journal_find_nth_type(LITERAL, 0);

	return (string && literal && string->index > literal->index);
}

t_bool			parse_expand()
{
	if (parse_should_expand_literals())
	{
		if (!parse_expand_strings(LITERAL))
			return (FALSE);
	}
	if (!parse_expand_variables())
		return (FALSE);
	if (!parse_expand_strings(STRING))
		return (FALSE);
	return (TRUE);
}

t_bool			parse_keep_matching()
{
	return (g_parser__->matcharea.begin < g_parser__->matcharea.end);
}

char			*parse_build_argument(size_t index)
{
	t_token		*token;
	char		*arg;

	token = journal_get(index);
	assert(token);
	if (token && token->type != SPACE && token->type != NULLBYTE)
	{
		arg = journal_get_string_for_index(index);
		assert(arg);
		return (arg);
	}
	return (NULL);
}

char			*parse_build_path(t_range *area)
{
	if (journal_at_index_is_type(area->begin, SPACE))
	{
		area->begin += 1;
		return (journal_get_string_for_index(area->begin));
	}
	else
	{
		return (journal_get_string_for_index(area->begin));
	}
}

t_argv			*parse_build_argv(t_range area)
{
	char		*arg;
	int			len;
	t_argv		*argv;

	len = range_len(area);
	argv = argv_create(len);
	if (argv)
	{
		while (len > 0)
		{
			arg = parse_build_argument(area.begin);
			if (arg)
				argv_push(argv, arg);
			area.begin++;
			len--;
		}
	}
	return (argv);
}

t_command		*parse_build_command(t_range area)
{
	char		*path;
	t_argv		*argv;
	t_command	*command;

	path = parse_build_path(&area);
	argv = parse_build_argv(area);
	command = command_create(path, argv);

	/* handle non-default file descriptors for command */

	return (command);
}


t_exec_op_type	parse_get_op_type_for_pattern(t_range area, t_bash_pattern_type pat_type)
{
	t_exec_op_type	op_type;

	if (pat_type == P_COMMAND || pat_type == P_PATH) /* hacky but needed */
		op_type = execscheme_get_op_type_for_token(journal_get(area.begin));
	else if (pat_type == P_ASSIGNMENT)
		op_type = OP_ASSIGNMENT;
	else if (pat_type == P_PATH)
		op_type = OP_PATH;
	else
		op_type = OP_NO_TYPE;
	return (op_type);
}

t_execscheme	*parse_build_execscheme(t_range area, t_bash_pattern_type pat_type)
{
	t_execscheme *scheme;

	scheme = execscheme_create();
	if (scheme)
	{
		/* put this in seperate functions */
		scheme->rel_type[NEXT_R] = execscheme_get_relation_type_for_token(journal_get(area.end));
		scheme->op_type = parse_get_op_type_for_pattern(area, pat_type);
		scheme->cmd = parse_build_command(area);
		assert(scheme->cmd);
	}
	return (scheme);
}

t_execscheme	*parse_get_next_scheme()
{
	t_range				my_area;
	t_bash_pattern_type	pat_type;

	my_area = g_parser__->matcharea;
	while (my_area.end > my_area.begin)
	{
		pat_type = bash_match_pattern(range(my_area.begin, my_area.end - 1)); /* 1 less because .end is length, not index! */
		if (pat_type != P_NO_TYPE)
		{
			/* found a match */
			dbg("found pattern %s for range {%i, %i}\n", pattern_dump_type(pat_type), my_area.begin, my_area.end);
			g_parser__->matcharea.begin = my_area.end + 1; /* 1 extra for skipping the delimiter */
			return (parse_build_execscheme(my_area, pat_type));
		}
		my_area.end--;
	}
	return (NULL);
}

void			parse_reset_match_area()
{
	g_parser__->matcharea = range(0, journal_size());
}

void			parse_dump_match_area(t_range area)
{
	char *range = range_dump(area);
	char *tokens = journal_dump_tokens_for_range(area);
	dbg("area: %s, tokens: %s\n", range, tokens);
	free(range);
	free(tokens);
}

t_execscheme	*parse_generate_execschemes()
{
	t_execscheme *root;
	t_execscheme *scheme;

	root = NULL;
	parse_reset_match_area();
	parse_dump_match_area(g_parser__->matcharea);
	
	while((scheme = parse_get_next_scheme()))
	{
		if (!root)
		{
			root = scheme;
			scheme->rel_type[PREV_R] = REL_START;
		}
		else
			execscheme_attach(root, scheme);
	}
	return (root);
}

t_execscheme	*parse()
{
	if (!parse_expand())
		return (NULL);
	if (g_parser__->rootscheme)
		execscheme_destroy(&g_parser__->rootscheme);
	g_parser__->rootscheme = parse_generate_execschemes();

	return (g_parser__->rootscheme);
}

t_parser	*parser_create()
{
	t_parser *parser;

	if (g_parser__)
		return (g_parser__);
	parser = ft_calloc(sizeof(t_parser), 1);
	if (parser)
	{
	}
	return ((g_parser__ = parser));
}

t_parser	*parser_destroy(t_parser **parser)
{
	if (!g_parser__)
		return (NULL);
	execscheme_destroy(&g_parser__->rootscheme);
	free(g_parser__);
	g_parser__ = NULL;
	if (parser)
		*parser = NULL;
	return ((g_parser__ = NULL));
}

void		parser_set_env(t_env *env)
{
	assert(g_parser__);
	assert(! g_parser__->env);
	g_parser__->env = env;
}
