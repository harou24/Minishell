/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.cpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:13:55 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:14:00 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <catch2/catch.hpp>

extern "C" {
# include "token.h"
# include "journal.h"
# include "lexer.h"
}

TEST_CASE( "create_destroy token", "[token]" ) {
	t_token *token;

	CHECK((token = token_create(range(1, 1), TOKEN_TYPE_SIZE)));
	CHECK((token = token_destroy(token)) == NULL);
}

TEST_CASE( "token_cmp", "[token]" ) {
	t_token *a, *b;

	a = token_create(range(1, 1), TOKEN_TYPE_SIZE);
	b = token_create(range(1, 1), TOKEN_TYPE_SIZE);
	a->type = TOKEN_TYPE_SIZE;
	b->type = a->type;
	CHECK(token_cmp(a, b) == 0);
	b->type = SPACE;
	CHECK(token_cmp(a, b) == 1);
	token_destroy(a);
	token_destroy(b);
}

TEST_CASE( "range", "[token]" ) {
	t_range r = range(1, 10);
	CHECK(r.begin == 1);
	CHECK(r.end == 10);
}
