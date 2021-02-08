NAME = minishell

SRC_D  = src
INC_D = inc
OBJ_D = obj
LIB_D = lib

SRC = $(SRC_D)/minishell.c

INC = $(INC_D)/minishell.h

OBJ := $(SRC:$(SRC_D)/%.c=$(OBJ_D)/%.o)

LIBFT = $(LIB_D)/libft/libft.a

LIB_INC = $(LIB_D)/libft/inc

CC = clang
CC_FLAGS = -Wall -Werror -Wextra

ifdef DEBUG
 CC_FLAGS += -g -fsanitize=address
endif


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_D) $(OBJ) $(INC_D) $(INC)
	@$(CC) $(CC_FLAGS) $(OBJ) -o$(NAME)

$(OBJ_D):
	@mkdir -p $(OBJ_D)

$(OBJ): $(OBJ_D)/%.o: $(SRC_D)/%.c
	@$(CC) $(CC_FLAGS) -I$(INC_D) -I$(LIB_INC) -c $< -o $@

$(LIBFT):
	@make -C $(LIB_D)/libft

clean:
	@rm -rf $(OBJ_D)
	@rm	-rf *.dSYM
	@make -C $(LIB_D)/libft clean

fclean: clean
	@rm -f $(NAME)
	@rm -f test
	@make -C $(LIB_D)/libft fclean

test: $(NAME)
	@$(CC) $(CC_FLAGS) -I$(INC_D) -I$(LIB_INC) -o test tests/main.c $(NAME) lib/libft/libft.a 
	@./test

submodule:
	@git submodule init
	@git submodule update
	
re: fclean all
