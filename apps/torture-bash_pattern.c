/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   torture-bash_pattern.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:11:02 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:11:03 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DEBUG 1

#include "lexer.h"
#include "parser.h"
#include "bash_pattern.h"

int main (int argc, char **argv)
{
	if (argc ==  3)
	{
		bool err = FALSE;
		t_lex *lexer = lex_create();
		t_parser *parser = parser_create();
		if (lex(argv[1]))
		{
			char *for_human = journal_dump_tokens();
			printf("%30s : %s\n", "LEX TOKENS", for_human);
			free(for_human);

			if (!parse_expand())
			{
				printf("PARSE EXPAND FAILED\n");
				err = true;
			}
			else
			{
				for_human = journal_dump_tokens();
				printf("%30s : %s\n", "POST-PARSE TOKENS", for_human);
				free(for_human);

				for_human = journal_reconstruct_string();
				printf("%30s : %s\n", "RECONSTRUCTED STRING", for_human);
				free(for_human);

				char *endptr;
				int match_len = strtod(argv[2], &endptr);
				assert(*endptr == '\0');
				assert(match_len > 0);

				t_bash_pattern_type pattern = bash_match_pattern(range(0, match_len - 1));
				for_human = pattern_dump_type(pattern);
				printf("%30s : %s\n", "MATCHED COMMAND", for_human);
			}
		}
		else
		{
			printf("ERROR\n");
			err = TRUE;
		}
		lex_destroy(&lexer);
		parser_destroy(&parser);
		return (err);
	}
	else
	{
		return (1);
	}
}
