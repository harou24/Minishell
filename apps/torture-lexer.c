#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"

int main (int argc, char **argv)
{
	if (argc == 2)
	{
		bool err = FALSE;
		t_lex *lexer = lex_create();
		if (lex(argv[1]))
		{
			char *for_human = journal_dump_tokens();
			printf("TOKENS : %s\n", for_human);
			free(for_human);
		}
		else
		{
			printf("ERROR\n");
			err = TRUE;
		}
		lex_destroy(&lexer);
		return (err);
	}
	else
	{
		return (1);
	}
}
