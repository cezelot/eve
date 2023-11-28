NAME	= eve

CC	= gcc

FLAGS	= -Wall -Werror -Wextra -pedantic -std=c99 -O2

SOURCES	= sources/main.c sources/terminal.c sources/input.c

all	:
	$(CC) $(FLAGS) $(SOURCES) -o $(NAME)

fclean	:
	rm -f $(NAME)

re	: fclean all
