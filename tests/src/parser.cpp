#include <cstring>
#include <catch2/catch.hpp>

extern "C" {
# include "token.h"
# include "journal.h"
# include "lexer.h"
# include "parser.h"
}

TEST_CASE( "parser construction/destruction", "[parser]" ) {
	t_parser *parser = parser_create();
	CHECK(parser != NULL);
	
	CHECK(parser_destroy(&parser) == NULL);
	CHECK(parser == NULL);
}

/*
TEST_CASE( "string expansion", "[parser]" ) {
	struct s_tst {
		const char *key;
		const char *tokens;
	};
	static const s_tst tests[] =	{
										{ "",		"" },
										{ "''",		"''" },
									};
	lex_create();
	parse_create();
	const size_t testslen = sizeof(tests)/sizeof(s_tst);
	for (size_t i = 0; i < testslen; i++) {
		CHECK(lex(tests[i].key) != NULL);
		char *r = journal_dump_tokens();
		printf("%20s: %s\n", "KEY", tests[i].key);
		printf("%20s: %s\n", "REF TOKENS", tests[i].tokens);
		printf("%20s: %s\n", "RETURNED TOKENS", r);
		CHECK(strcmp(r, tests[i].tokens) == 0);
		free(r);
	}
	lex_destroy(NULL);
	parse_destroy(NULL);
}
*/
