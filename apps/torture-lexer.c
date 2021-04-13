/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   torture-lexer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:11:15 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:11:15 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"

int main (int argc, char **argv)
{
	if (argc >=  2)
	{
		bool err = FALSE;
		t_lex *lexer = lex_create();
		for (int i = 1; i < argc; i++) {
			if (lex(argv[i]))
			{
				char *for_human = journal_dump_tokens();
				printf("TOKENS : %s\n", for_human);
				free(for_human);
			}
			else
			{
				printf("ERROR\n");
				err = TRUE;
				break;
			}
		}
		lex_destroy(&lexer);
		return (err);
	}
	else
	{
		return (1);
	}
}
