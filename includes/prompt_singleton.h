/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt_singleton.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:10:25 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:10:26 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_SINGLETON_H
# define PROMPT_SINGLETON_H

# include "libft.h"
# include "prompt.h"

t_prompt	*prompt_init(void);
void		prompt_deinit(t_prompt **prompt);

char		*prompt(int last_error);

#endif
