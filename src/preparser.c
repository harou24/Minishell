/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   preparser.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:04:28 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:04:30 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stdlib.h>

#include "libft.h"

#include "debugger.h"
#include "bash_pattern.h"
#include "parser.h"
#include "env_singleton.h"
#include "journal.h"

t_range	preparser_get_next_area(void)
{
	t_token			*token;
	t_range			matchrange;

	matchrange = range(0, 0);
	while (journal_get(0) && journal_get(0)->type == SEMICOLON)
		journal_remove(0);
	journal_rebuild_tokens();
	token = journal_get(matchrange.end);
	while (token)
	{
		if (token->type == SEMICOLON || token->type == NULLBYTE)
			return (range(matchrange.begin, matchrange.end + 1));
		matchrange.end++;
		token = journal_get(matchrange.end);
	}
	return (range(0, 0));
}
