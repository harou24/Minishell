/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:13:16 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:13:23 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <catch2/catch.hpp>

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
	t_range	r;
	char	*notre_r_str;
	char	*votre_r_str;

	token = journal_creeper_next();
	REQUIRE(token != NULL);
	r = range(0, 2);
	notre_r_str = range_dump(r);
	votre_r_str = range_dump(token->range);
	printf("range : notre %s votre %s\n", notre_r_str, votre_r_str);
	free(notre_r_str); free(votre_r_str);
	CHECK(range_cmp(r, token->range) == 0);
	
	token = journal_creeper_next();
	REQUIRE(token != NULL);
	r = range(3, 3);
	notre_r_str = range_dump(r);
	votre_r_str = range_dump(token->range);
	printf("range : notre %s votre %s\n", notre_r_str, votre_r_str);
	free(notre_r_str); free(votre_r_str);
	CHECK(range_cmp(r, token->range) == 0);

	token = journal_creeper_next();
	REQUIRE(token != NULL);
	r = range(4, 6);
	notre_r_str = range_dump(r);
	votre_r_str = range_dump(token->range);
	printf("range : notre %s votre %s\n", notre_r_str, votre_r_str);
	free(notre_r_str); free(votre_r_str);
	CHECK(range_cmp(r, token->range) == 0);
	
	CHECK(lex_destroy(&lexer) == NULL);
	CHECK(lexer == NULL);
}

TEST_CASE( "basic lexing", "[lexer]" ) {
	struct s_tst {
		const char *key;
		const char *tokens;
	};
	static const s_tst tests[] =	{
										{ "",						"NULLBYTE " },
										{ "a",						"WORD NULLBYTE " },
										{ " \a\b\r\t\f\v",			"SPACE NULLBYTE " },
										{ "echo a",					"WORD SPACE WORD NULLBYTE " },
										{ "\"\"",					"STRING STRING NULLBYTE " },
										{ "\'\'",					"LITERAL LITERAL NULLBYTE " },
										{ "a=5",					"WORD ASSIGNMENT WORD NULLBYTE " },
										{ "$a$",					"VARIABLE WORD VARIABLE NULLBYTE " },
										{ "a\n",					"WORD NEWLINE NULLBYTE " },
										{ "\"\\\"\"",				"STRING ESCAPE STRING STRING NULLBYTE " },
										{ "a   \n b",				"WORD SPACE NEWLINE SPACE WORD NULLBYTE " },
										{ "echo a | cat",			"WORD SPACE WORD SPACE PIPE SPACE WORD NULLBYTE " },
										{ "echo a ; echo b",		"WORD SPACE WORD SPACE SEMICOLON SPACE WORD SPACE WORD NULLBYTE " },
										{ "echo a >> f",			"WORD SPACE WORD SPACE APPEND SPACE WORD NULLBYTE " },
										{ "echo a > f",				"WORD SPACE WORD SPACE WRITE SPACE WORD NULLBYTE " },
										{ "cat < f",				"WORD SPACE READ SPACE WORD NULLBYTE " }
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
