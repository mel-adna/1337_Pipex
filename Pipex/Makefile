CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
RM = rm -f
LIBFT_DIR = libft
BONUS_DIR = bonus
SRC =  pipex.c parse.c pipex_utils.c 
OBJ = $(SRC:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a
BONUS = $(BONUS_DIR)/pipex_bonus

all: $(LIBFT) $(NAME)

bonus: $(LIBFT) $(BONUS)

$(BONUS):
	@$(MAKE) -C $(BONUS_DIR)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(BONUS_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(BONUS_DIR) fclean

re: fclean all

.PHONY: all clean fclean re