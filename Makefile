NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

#Main project source files
SRCS = src/pipex.c src/error_handling.c src/command.c
OBJS = $(SRCS:.c=.o)

#Bonus source files
SRC_BONUS = src_bonus/main.c src_bonus/utils.c src_bonus/process.c src_bonus/heredoc.c src_bonus/exe.c src_bonus/error_handling_bonus.c
OBJS_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re bonus

