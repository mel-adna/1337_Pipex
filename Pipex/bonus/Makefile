CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = ../pipex_bonus
RM = rm -f
LIBFT_DIR = ../libft
SRC = gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c pipex.c parse.c \
	pipex_utils.c pipex_utils1.c 
OBJ = $(SRC:.c=.o)
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT)

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re