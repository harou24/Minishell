# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/13 21:15:17 by sverschu      #+#    #+#                  #
#    Updated: 2021/04/14 19:35:35 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = MINISHELL_MOCKTARGET

MINIMAKE = ./minimake.sh

all: $(NAME)

cmake_RULE:
	@which cmake || { [[ `uname` == "Darwin" ]] && brew install cmake; } \
		|| { echo "Install cmake first."; exit 1; }

$(NAME): cmake_RULE
	@$(MINIMAKE) release
debug: cmake_RULE
	@$(MINIMAKE) debug
test: cmake_RULE
	@$(MINIMAKE) test

clean:
	@mv minishell minishell.DONTTOUCHME || true
	@mv libminishell.a libminishell.a.DONTTOUCHME || true
	@$(MINIMAKE) clean
	@mv minishell.DONTTOUCHME minishell || true
	@mv libminishell.a.DONTTOUCHME libminishell.a || true

fclean: clean
	@$(MINIMAKE) clean

re: fclean all

.PHONY = clean fclean re $(NAME)
