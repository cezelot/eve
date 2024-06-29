# Copyright (C) 2024 cezelot.
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

SRC_DIR   := ./sources

SRC_FILES := main.c \
             options.c \
             append_buffer.c \
             file_io.c \
             row_operations.c \
             terminal/terminal.c \
             terminal/terminal_utils.c \
             terminal/terminal_utils_2.c \
             input/input.c \
             input/input_utils.c \
             input/input_utils_2.c \
             output/output.c \
             output/output_utils.c

OBJ_DIR   := ./objects

OBJS      := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@echo
	$(CC) $(FLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p `dirname $@`
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -Rf $(OBJ_DIR)/

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
