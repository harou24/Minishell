/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filesystem_traversal.cpp                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 21:12:36 by sverschu      #+#    #+#                 */
/*   Updated: 2021/04/13 21:12:54 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <catch2/catch.hpp>

extern "C" {
# include "filesystem.h"
# include "filesystem_traversal.h"
}

#include <string.h>
#include <unistd.h>

 TEST_CASE( "fs_get_cur_dir_name", "[dir]" ) {
	 char *cur_dir = fs_get_cur_dir_name();
	 char buffer[1024];
	 
	 CHECK(strcmp(cur_dir, getcwd(buffer, 1024)) == 0);
	 free(cur_dir);
 }

 TEST_CASE( "fs_change_dir", "[dir]" ) {
	CHECK(fs_change_dir("non_existing_dir__________________") != 0);
 }

 TEST_CASE("directory_exist", "dir") {
	CHECK(directory_exists("non_existing_dir______________________") == FALSE);
 }
