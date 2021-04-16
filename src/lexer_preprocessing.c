/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_preprocessing.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:03:10 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:03:12 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "vector.h"
#include "lexer.h"
#include "token.h"
#include "string_processing.h"
#include "bash_sym.h"

extern t_lex	*g_lex__;

char	*lexer_preprocess_string(const char *str)
{
	return (string_replace_escaped_chars(str));
}
