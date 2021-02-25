#include <cstring>
#include <catch2/catch.hpp>

/*
 * Catch2: examples
 * for more examples checkout:
 *   https://github.com/catchorg/Catch2/tree/devel/examples
 *
 * Catch has two natural expression assertion macro's:
 * - REQUIRE() stops at first failure.
 * - CHECK() continues after failure.
 *
 * There are two variants to support decomposing negated expressions:
 * - REQUIRE_FALSE() stops at first failure.
 * - CHECK_FALSE() continues after failure.
 *
 * TEST_CASE( "Title here", "[short name]" ) {
 *     REQUIRE( [BOOLEAN CONDITION] ) ;
 * }
 */

extern "C" {
# include "token.h"
# include "journal.h"
# include "lexer.h"
}

TEST_CASE( "construction/destruction", "[lexer]" ) {
	t_lex *lexer = lex_create();
	CHECK(lexer != NULL);
	
	CHECK(lex_destroy(&lexer) == NULL);
	CHECK(lexer == NULL);
}

TEST_CASE("ranges", "[lexer]") {
	t_lex *lexer = lex_create();
	CHECK(lexer != NULL);
	char *str = (char *)"012 456";

	lex(str);

	/* get every token and manually verify range*/
	t_token *token;
	t_range	range;
	char	*notre_r_str;
	char	*votre_r_str;

	token = journal_creeper_next();
	REQUIRE(token != NULL);
	range = {0, 2};
	notre_r_str = range_dump(range);
	votre_r_str = range_dump(token->range);
	printf("range : notre %s votre %s\n", notre_r_str, votre_r_str);
	free(notre_r_str); free(votre_r_str);
	CHECK(range_cmp(range, token->range) == 0);
	
	token = journal_creeper_next();
	REQUIRE(token != NULL);
	range = {3, 3};
	notre_r_str = range_dump(range);
	votre_r_str = range_dump(token->range);
	printf("range : notre %s votre %s\n", notre_r_str, votre_r_str);
	free(notre_r_str); free(votre_r_str);
	CHECK(range_cmp(range, token->range) == 0);

	token = journal_creeper_next();
	REQUIRE(token != NULL);
	range = {4, 6};
	notre_r_str = range_dump(range);
	votre_r_str = range_dump(token->range);
	printf("range : notre %s votre %s\n", notre_r_str, votre_r_str);
	free(notre_r_str); free(votre_r_str);
	CHECK(range_cmp(range, token->range) == 0);
	
	CHECK(lex_destroy(&lexer) == NULL);
	CHECK(lexer == NULL);
}

TEST_CASE( "basic lexing", "[lexer]" ) {
	struct s_tst {
		const char *key;
		const char *tokens;
	};
	static const s_tst tests[] =	{
										{ "",						"" },
										{ "a",						"WORD " },
										{ " \a\b\r\t\f\v",			"SPACE " },
										{ "echo a",					"WORD SPACE WORD " },
										{ "\"\"",					"STRING STRING " },
										{ "\'\'",					"LITERAL LITERAL " },
										{ "a=5",					"WORD ASSIGNMENT WORD " },
										{ "$a$",					"VARIABLE WORD VARIABLE " },
										{ "a\n",					"WORD NEWLINE " },
										{ "\"\\\"\"",				"STRING ESCAPE STRING STRING " },
										{ "a   \n b",				"WORD SPACE NEWLINE SPACE WORD " },
										{ "echo a | cat",			"WORD SPACE WORD SPACE PIPE SPACE WORD " },
										{ "echo a ; echo b",		"WORD SPACE WORD SPACE SEMICOLON SPACE WORD SPACE WORD " },
										{ "echo a >> f",			"WORD SPACE WORD SPACE OP_APPEND SPACE WORD " },
										{ "echo a > f",				"WORD SPACE WORD SPACE OP_WRITE SPACE WORD " },
										{ "cat < f",				"WORD SPACE OP_READ SPACE WORD " }
									};
	lex_create();
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
}
