SRCS	= main.c terminal.c input.c

NAME	= eve

OBJS	= ${SRCS:.c=.o}

HEADERS	= includes/

.c.o	:
	gcc -Wall -Werror -Wextra -pedantic -std=c99 -g -I ${HEADERS} -c $< -o ${<:.c=.o}

${NAME}	: ${OBJS}
	gcc -Wall -Werror -Wextra -pedantic -std=c99 -g -I ${HEADERS} ${OBJS} -o ${NAME}

all : ${NAME}

clean	:
	rm -f ${OBJS}

fclean	:
	rm -f ${NAME}

re : fclean all
