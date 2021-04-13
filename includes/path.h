/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:10:13 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:10:14 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "libft.h"

t_bool	path_contains(const char *path, const char *name);

char	*path_expand(const char *path, const char *name);

#endif
