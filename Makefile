NAME      = eve

CC        = gcc
FLAGS     = -Wall -Werror -Wextra -pedantic -std=c99

SRC_DIR   = ./sources

SRC_FILES = main.c \
            terminal/terminal.c \
            terminal/terminal_utils.c \
            append_buffer.c \
            file_io.c \
            row_operations.c \
            output/output.c \
            output/output_utils.c \
            input/input.c \
            input/input_utils.c \
            input/input_utils_2.c

OBJ_DIR   = ./objects

OBJS      = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@ echo
	$(CC) $(FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@ mkdir -p `dirname $@`
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -Rf $(OBJ_DIR)/

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean
