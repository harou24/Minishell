# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sverschu <sverschu@student.codam.n>          +#+                      #
#                                                    +#+                       #
#    Created: 2021/04/13 21:15:17 by sverschu      #+#    #+#                  #
#    Updated: 2021/04/13 21:15:19 by sverschu      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = MINISHELL_MOCKTARGET

MINIMAKE = ./minimake.sh

all: $(NAME)

$(NAME): 
	@which cmake || { [[ "$OSTYPE" == "darwin"* ]] && brew install cmake; } \
		|| { echo "Install cmake first."; exit 1; }
	$(MINIMAKE) release

clean:
	$(MINIMAKE) clean

fclean: clean
	$(MINIMAKE) clean

re: fclean all
