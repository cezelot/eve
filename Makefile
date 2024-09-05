# Copyright (C) 2024 Ismael Benjara
#
# This file is part of eve.
#
# eve is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# eve is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with eve.  If not, see <https://www.gnu.org/licenses/>.

NAME      := eve

CC        := gcc
FLAGS     := -Wall -Werror -Wextra -pedantic -std=c99

SRC_DIR   := src

SRC_FILES := main.c \
             append_buffer.c \
             editor_operations.c \
             find.c \
             options.c \
             syntax_highlighting.c \
             file/file_io.c \
             file/save_file_operations.c \
             input/input.c \
             input/input_2.c \
             input/input_3.c \
             input/input_4.c \
             input/key_handlers.c \
             output/output.c \
             output/output_2.c \
             row_operations/row_operations.c \
             row_operations/row_operations_2.c \
             terminal/terminal.c \
             terminal/terminal_2.c \
             terminal/terminal_3.c

OBJ_DIR   := objs

OBJS      := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p `dirname $@`
	$(CC) $(FLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS)
	@echo
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -Rf $(OBJ_DIR)/

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
