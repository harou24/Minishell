/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filesystem_traversal.h                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:09:44 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:09:45 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILESYSTEM_TRAVERSAL_H
# define FILESYSTEM_TRAVERSAL_H

# undef PATH_DEF
# define PATH_DEF	256

# undef PATH_MAX
# define PATH_MAX	4096

char	*fs_get_cur_dir_name(void);

int		fs_change_dir(const char *dname);

#endif
