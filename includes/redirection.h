/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirection.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:08:48 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:08:49 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "vector.h"
# include "libft.h"

# include "token.h"

typedef enum e_redirection_type
{
	RED_NO_TYPE =	0,
	RED_READ =		1<<1,
	RED_APPEND =	1<<2,
	RED_WRITE =		1<<3,
	RED_TAB_SIZE
}	t_redirection_type;

typedef struct s_redirection
{
	void			*vec[RED_TAB_SIZE];
}	t_redirection;

t_redirection_type	redir_get_type_for_token(t_token *token);

char				*redir_get(t_redirection *redirection,
						t_redirection_type type,
						size_t index);
t_bool				redir_push(t_redirection *redirection,
						t_redirection_type type,
						char *fname);

size_t				redir_get_size(t_redirection *redirection,
						t_redirection_type type);
t_bool				redir_has_redirections(t_redirection *redir);

t_redirection		*redir_create(void);
t_redirection		*redir_destroy(t_redirection **redirection);

t_bool				redir_perform_redirection(t_redirection *redir,
						t_redirection_type type, size_t index);
t_bool				redir_perform_redirections(t_redirection *redir);

/* redirection_utility.c */
t_bool				redir_stdout_to_file(const char *fname, t_bool append);
t_bool				redir_file_to_stdin(const char *fname);

t_bool				redir_stdout_to_pipe(int pipe[2]);
t_bool				redir_pipe_to_stdin(int pipe[2]);
void				redir_std_push(void);
void				redir_std_pop(void);

/* redirection_debugging.c */
void				redir_pretty_dump(t_redirection *redirection,
						int indent);
void				redir_pretty_dump_for_type(t_redirection *redir,
						t_redirection_type type, int indent);

#endif
