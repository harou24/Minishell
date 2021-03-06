#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "parser.h"

int main (int argc, char **argv)
{
	if (argc >=  2)
	{
		bool err = FALSE;
		t_lex *lexer = lex_create();
		t_parser *parser = parser_create();
		for (int i = 1; i < argc; i++) {
			if (lex(argv[i]))
			{
				char *for_human = journal_dump_tokens();
				printf("%30s : %s\n", "LEX TOKENS", for_human);
				free(for_human);

				//parse_expand_strings(journal_create());
				t_execscheme *rootscheme;
				rootscheme = parse(journal_create());
				if (!rootscheme) {
					printf("%30s\n", "PARSE FAILED");
					break;
				}
				execscheme_pretty_dump(rootscheme, 15);

				for_human = journal_dump_tokens();
				printf("%30s : %s\n", "POST-PARSE TOKENS", for_human);
				free(for_human);

				for_human = journal_reconstruct_string();
				printf("%30s : %s\n", "RECONSTRUCTED STRING", for_human);
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
		parser_destroy(&parser);
		return (err);
	}
	else
	{
		return (1);
	}
}
