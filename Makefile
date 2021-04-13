NAME = MINISHELL_MOCKTARGET

MINIMAKE = ./minimake.sh

all: $(NAME)

$(NAME): 
	$(MINIMAKE) release

clean:
	$(MINIMAKE) clean

fclean: clean
	$(MINIMAKE) clean

re: fclean all
