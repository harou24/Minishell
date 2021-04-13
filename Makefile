NAME = MINISHELL_MOCKTARGET

MINIMAKE = ./minimake.sh

all: $(NAME)

$(NAME): 
	@which cmake || { [[ "$OSTYPE" == "darwin"* ]] && brew install cmake; } \
		|| echo "Install cmake first."
	$(MINIMAKE) release

clean:
	$(MINIMAKE) clean

fclean: clean
	$(MINIMAKE) clean

re: fclean all
