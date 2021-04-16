/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argv.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:08:48 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:08:49 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGV_H
# define ARGV_H

# include "vector.h"
# include "libft.h"

typedef struct s_argv
{
	void			*vec;
}					t_argv;

char				*argv_get(t_argv *argv, int index);
t_bool				argv_push(t_argv *argv, char *arg);

const char			**argv_get_array(t_argv *argv);
size_t				argv_get_size(t_argv *argv);

t_argv				*argv_create(char *path);
t_argv				*argv_destroy(t_argv **argv);

void				argv_pretty_dump(t_argv *argv, int indent);

/* argv_transform.c */
t_bool				argv_transform_escape_chars(t_argv *argv);

#endif
