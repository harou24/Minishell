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

TEST_CASE( "create_destroy journal", "[journal]" ) {
	t_journal *journal_static;

	CHECK((journal_static = journal_create()));
	CHECK(memcmp(journal_static, journal_create(), sizeof(t_journal)) == 0);
	CHECK((journal_static = journal_destroy(NULL)) == NULL);
}

TEST_CASE("push_get_size_clear", "[journal]") {
	journal_create();
	const size_t lim = 1000;

	for (unsigned int i = 0; i < lim; i++)
	{
		CHECK(journal_size() == i);
		CHECK(journal_push(token_create(range(0, 1), (e_token_type)(TOKEN_TYPE_SIZE - 1))));
		CHECK(journal_get(i));
	}
	CHECK(journal_size() == lim);
	journal_clear();
	CHECK(journal_size() == 0);
	
	journal_destroy(NULL);
}

TEST_CASE("has_token/type", "[journal]") {
	journal_create();

	t_range sample_range = range(0, 1);
	t_token *token_a = token_create(sample_range, SPACE);
	t_token *token_b = token_create(sample_range, WORD);

	journal_push(token_a);
	CHECK(journal_has_token(token_a));
	CHECK(journal_has_tokentype(token_a->type));
	CHECK_FALSE(journal_has_token(token_b));
	CHECK_FALSE(journal_has_tokentype(token_b->type));

	token_destroy(token_b);
	journal_destroy(NULL);
}

TEST_CASE("find_first_last_token_type", "[journal]") {
	journal_create();

	t_range sample_range = range(0, 1);
	for (size_t i = 0; i < TOKEN_TYPE_SIZE - 1; i++) {
		t_token *t = token_create(sample_range, (e_token_type)i);
		journal_push(t);
	}
	for (size_t i = 0; i < TOKEN_TYPE_SIZE - 1; i++) {
		t_token *t = token_create(sample_range, (e_token_type)i);
		CHECK(journal_find_first_token(t)->type == t->type);
		CHECK(journal_find_first_type(t->type)->type == t->type);
		CHECK(journal_find_last_token(t)->type == t->type);
		CHECK(journal_find_last_type(t->type)->type == t->type);
		CHECK(memcmp(t, journal_find_first_token(t), sizeof(t_token)) == 0);
		token_destroy(t);
	}
	t_token *t = token_create(sample_range, SPACE);
	journal_push(t);
	CHECK(journal_find_first_token(t) != t);
	CHECK(journal_find_first_type(t->type)->type == t->type);
	CHECK(journal_find_last_token(t) == t);
	CHECK(journal_find_last_type(t->type)->type == t->type);

	journal_destroy(NULL);
}

TEST_CASE("creeper_next_reset_set_get", "[journal]") {
	journal_create();

	t_range sample_range = range(0, 1);
	for (size_t i = 0; i < TOKEN_TYPE_SIZE; i++) {
		t_token *t = token_create(sample_range, (e_token_type)i);
		journal_push(t);
	}

	CHECK(journal_size() == (size_t)TOKEN_TYPE_SIZE);

	for (size_t i = 0; i < TOKEN_TYPE_SIZE; i++) {
		t_token *t = journal_creeper_next();
		REQUIRE(t);
		CHECK(t->type == (e_token_type)i);
	}
	CHECK(journal_creeper_next() == NULL);

	journal_creeper_reset();

	for (size_t i = 0; i < TOKEN_TYPE_SIZE; i++) {
		t_token *t = journal_creeper_next();
		REQUIRE(t);
		CHECK(t->type == (e_token_type)i);
	}
	CHECK(journal_creeper_next() == NULL);
	
	CHECK(journal_creeper_get_index() == (size_t)TOKEN_TYPE_SIZE);
	journal_creeper_set_index(SPACE);
	CHECK(journal_creeper_get_index() == (size_t)SPACE);
	
	journal_destroy(NULL);
}

/*
TEST_CASE("", "[journal]") {
	journal_create();
	
	journal_destroy(NULL);
}
*/
