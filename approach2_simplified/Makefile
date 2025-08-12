# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wsm <wsm@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/11 12:30:00 by wsm               #+#    #+#              #
#    Updated: 2024/08/11 12:30:00 by wsm              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCDIR = src
INCDIR = include

SOURCES = main.c \
		  process.c \
		  execute.c \
		  utils.c \
		  heredoc.c \
		  string_utils.c \
		  ft_split.c

SRCS = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: $(NAME)
	@echo "🚀 Testing Simplified Approach2 Pipex..."
	@echo "Creating test files..."
	@echo -e "hello world\ntest line\nfinal line" > test_input.txt
	@echo -e "3\n1\n4\n2" > test_numbers.txt
	
	@echo "Test 1: Basic pipeline"
	./$(NAME) test_input.txt "grep test" "wc -l" output1.txt
	@echo "Result: $$(cat output1.txt)"
	
	@echo "Test 2: Multi-command pipeline"  
	./$(NAME) test_numbers.txt "sort -n" "head -2" "wc -l" output2.txt
	@echo "Result: $$(cat output2.txt)"
	
	@echo "Test 3: Heredoc"
	@echo -e "hello\nworld\nEND" | ./$(NAME) here_doc END "tr a-z A-Z" "wc -w" output3.txt
	@echo "Result: $$(cat output3.txt)"
	
	@echo "✅ All tests completed!"

valgrind: $(NAME)
	@echo "🔍 Testing for memory leaks with Valgrind..."
	@echo -e "test\ndata\nEOF" | valgrind --leak-check=full --show-leak-kinds=all \
		./$(NAME) here_doc EOF "cat" "wc -l" valgrind_output.txt

.PHONY: all clean fclean re test valgrind
