CC = cc
CFLAGS = -Wall -Wextra -Werror 
NAME = ../pipex
RM = rm -f
LIBFT_DIR = ../libft
SRC = gnl/get_next_line.c gnl/get_next_line_utils.c pipex.c parse.c \
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