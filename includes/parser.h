/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:10:09 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:10:10 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "range.h"
# include "journal.h"
# include "env.h"
# include "execscheme.h"

typedef struct s_parser
{
	t_execscheme	*rootscheme;
	t_range			matcharea;
	t_env			*env;
}					t_parser;

t_execscheme		*parse(t_range matcharea);

t_parser			*parser_create(void);
t_parser			*parser_destroy(t_parser **parser);

void				parser_set_env(t_env *env);

t_vector			parse_get_subtokens(t_token *first, t_token *last);
void				parse_replace_tokens_with_token(t_vector tokens,
						t_token *first, t_token *last, t_token *token);

void				parse_perform_string_substitution(t_vector tokens,
						t_token *first, t_token *last, t_vector subtokens);
t_bool				parse_expand_first_string(t_vector tokens,
						t_token *first, t_token *last);
t_bool				parse_expand_strings(t_token_type_e string_type);
t_bool				parse_should_expand_literals(void);

char				*parse_retreive_var_from_env_for_token(t_token *token);
void				parse_perform_var_substitution(t_vector tokens,
						t_token *var_sym, t_token *var_name);

t_bool				parse_expand_first_variable(t_vector tokens,
						t_token *var_sym);
t_bool				parse_expand_variables(void);
t_bool				parse_expand(void);

void				parse_dump_match_area(t_range area);
void				parse_reset_match_area(void);

char				*parse_build_path(t_range *matcharea);
char				*parse_build_argument(t_range *matcharea);

t_range				preparser_get_next_area(void);
t_execscheme		*parse_get_next_scheme(void);
t_execscheme		*parse_generate_execschemes(void);

void				parse_flush_tokens(t_range area);

t_bool				parse_is_token_in_matcharea(t_token *token);

t_bool				parse_extract_command_arguments(t_redirection *redir,
						t_command *cmd, t_range area);

#endif
