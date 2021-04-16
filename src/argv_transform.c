/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   argv_transform.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 20:56:10 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 20:56:17 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "vector.h"
#include "libft.h"
#include "debugger.h"
#include "string_processing.h"

#include "argv.h"

static int escape_transform(void **obj)
{
	if (*obj)
		string_replace_escaped_chars_inline((char *)*obj);
	return (1);
}

t_bool	argv_transform_escape_chars(t_argv *argv)
{
	return (vector(&argv->vec, V_TRANSFORM, 0, (void *)escape_transform)
		== NULL);
}
