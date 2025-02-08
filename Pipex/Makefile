CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
RM = rm -f
FT_PRINTF_DIR = ft_printf
LIBFT_DIR = libft
SRC = gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c pipex.c parse.c \
	pipex_utils.c 
OBJ = $(SRC:.c=.o)
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT = $(LIBFT_DIR)/libft.a

all: $(FT_PRINTF) $(LIBFT) $(NAME) clean

$(FT_PRINTF):
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(FT_PRINTF) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(FT_PRINTF) $(LIBFT)

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

run:
	@echo "\033[1;32m./pipex\033[0m"
	@echo "\033[1;33m--------\033[0m"
	@./$(NAME) in "ls -l" "cat -e" out

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(FT_PRINTF_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(FT_PRINTF_DIR) fclean
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re