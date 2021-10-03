NAME = pipex

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/

LIBFT = -L. -lft 


SRC_LIST = main.c error.c find_command.c execute_cmd.c
 
SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

GNL = $(addprefix $(GNL_DIR), $(GNL_LIST))

PARSER = $(addprefix $(PARSER_DIR), $(PARSER_LIST))

UTILS = $(addprefix $(UTILS_DIR), $(UTILS_LIST))

SRCS = $(SRC_LIST)

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) libft
	@echo "\n"
	@echo "\033[0;32mCompiling pipex..."
	@make -C libft/
	cp libft/libft.a .
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "\n\033[0mDone !"

%.o: %.c
	@printf "\033[0;33mGenerating pipex objects... %-33.33s\r" $@
	@${CC} -g ${CFLAGS} -c $< -o $@

clean:
	@echo "\033[0;31mCleaning libft..."
	@make clean -C libft/
	@echo "\nRemoving binaries..."
	@rm -f $(OBJ)
	@echo "\033[0m"

fclean:
	@echo "\033[0;31mCleaning libft..."
	@make fclean -C libft/
	@echo "\nDeleting objects..."
	@rm -f $(OBJ)
	@echo "\nDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[0m"

re: fclean all

test: all
	./$(NAME)

norm:
	norminette $(SRC) includes/$(HEADER)

.PHONY: clean fclean re test norm