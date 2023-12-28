NAME	= eve

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra -pedantic -std=c99

SRCS	= ./sources/main.c ./sources/terminal/terminal.c \
		  ./sources/terminal/terminal_2.c ./sources/append_buffer.c \
		  ./sources/output.c ./sources/input.c

OBJS	= $(SRCS:.c=.o)

RM		= rm -f

all		: $(NAME)

.c.o	:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean all
