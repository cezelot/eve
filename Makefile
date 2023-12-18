NAME	= eve

CC	= gcc

FLAGS	= -Wall -Werror -Wextra -pedantic -std=c99

SOURCES	= ./sources/main.c ./sources/terminal/*.c \
		  ./sources/append_buffer.c \
		  ./sources/output.c ./sources/input.c

all	:
	$(CC) $(FLAGS) $(SOURCES) -o $(NAME)

fclean	:
	rm -f $(NAME)

re	: fclean all
