/* ************************************************************************** */
/*                                                                            */
/*   eve.h                                                                    */
/*                                                                            */
/*   Created: 2023/11/27 17:17:10 by cezelot                                  */
/*   Updated: 2024/08/16 17:00:27 by alberrod                                 */
/*                                                                            */
/*   Copyright (C) 2024 Ismael B. Hamed, Alberto Rodriguez                    */
/*                                                                            */
/*   This file is part of eve.                                                */
/*                                                                            */
/*   eve is free software: you can redistribute it and/or modify              */
/*   it under the terms of the GNU General Public License as published by     */
/*   the Free Software Foundation, either version 3 of the License, or        */
/*   (at your option) any later version.                                      */
/*                                                                            */
/*   eve is distributed in the hope that it will be useful,                   */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*   GNU General Public License for more details.                             */
/*                                                                            */
/*   You should have received a copy of the GNU General Public License        */
/*   along with eve.  If not, see <https://www.gnu.org/licenses/>.            */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVE_H
# define EVE_H

# define _DEFAULT_SOURCE
# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# define PROGRAM_NAME "eve"
# define VERSION "0.4.0"
# define TAB_STOP 4

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <getopt.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <time.h>
# include <unistd.h>

enum e_editor_key
{
    // new keys
    NEWLINE_KEY = '\r',
    CTRL_Q = ('q' & 0x1f),
    CTRL_S = ('s' & 0x1f),
    CTRL_F = ('f' & 0x1f),

    // old keys
	CTRL_L = ('l' & 0x1f),
	CTRL_H = ('h' & 0x1f),
	ESC = '\x1b',
	BACKSPACE = 127,
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	DEL_KEY,
	HOME_KEY,
	END_KEY,
	PAGE_UP,
	PAGE_DOWN
};

typedef struct s_editor_row
{
	char	*chars;
	char	*render;
	int		size;
	int		rsize;
}			t_erow;

typedef struct s_editor_config
{
	int		cx;
	int		cy;
	int		rx;
	int		rowoff;
	int		coloff;
	int		screenrows;
	int		screencols;
	int		numrows;
	t_erow	*row;
	char	*filename;
	int		dirty;
    int     quit_times;
	char	statusmsg[80];
	time_t	statusmsg_time;
}			t_env;

typedef struct s_append_buffer
{
	char	*buf;
	int		len;
}			t_abuf;

typedef void (*t_key_handler)(t_env *env, int key);

typedef struct s_key_map
{
	int				key;
	t_key_handler	handler;
}					t_key_map;

// ------------------------------------------------------------------- main.c --
void	close_editor(t_env *env);
void	die(const char *format, ...);
// ---------------------------------------------------------- append_buffer.c --
void	abuf_append(t_abuf *abuf, const char *str, int len);
void	abuf_free(t_abuf *abuf);
// ------------------------------------------------------ editor_operations.c --
void	delete_char(t_env *env);
void	insert_char(t_env *env, int c);
void	insert_newline(t_env *env);
// ---------------------------------------------------------------- file_io.c --
void	open_file(t_env *env, char *filename);
void	save(t_env *env);
// --------------------------------------------------- save_file_operations.c --
void	cleanup(int fd, char *buf);
int		set_filename(t_env *env);
int		open_save_file(t_env *env, char *buf);
int		truncate_file(int fd, int len, char *buf, t_env *env);
int		write_file(int fd, int len, char *buf, t_env *env);
// ------------------------------------------------------------------- find.c --
void	find(t_env *env);
// ---------------------------------------------------------------- options.c --
void	parse_options(int ac, char **av, int *option_index);
// ------------------------------------------------------------------ input.c --
void	move_cursor(t_env *env, int key);
void	handle_keypress(t_env *env);
char	*prompt(t_env *env, char *message, \
				void (*callback)(t_env *, char *, int));
// ---------------------------------------------------------------- input_2.c --
void	move_cursor_down(t_env *env);
void	move_cursor_left(t_env *env);
void	move_cursor_right(t_env *env, t_erow *row);
void	move_cursor_up(t_env *env);
void	snap_cursor_to_end_line(t_env *env, t_erow *row, int rowlen);
// ---------------------------------------------------------------- input_3.c --
int		handle_special_keys(t_env *env, int key);
// ---------------------------------------------------------------- input_4.c --
void	move_cursor_to_end_line(t_env *env);
void	change_page(t_env *env, int key);
void    quit_program(t_env *env);
// ----------------------------------------------------------- key_handlers.c --
void	handle_page_keys(t_env *env, int key);
void	handle_position_keys(t_env *env, int key);
void	handle_deletion_keys(t_env *env, int key);
void    handle_insertion_keys(t_env *env, int key);
void    handle_signals(t_env *env, int key);
// ---------------------------------------------------- additional_handlers.c --
void	pending_to_handle(t_env *env, int key);
// ----------------------------------------------------------------- output.c --
void	draw_message_bar(t_env *env, t_abuf *abuf);
void	refresh_screen(t_env *env);
// --------------------------------------------------------------- output_2.c --
void	display_text_buffer(t_env *env, t_abuf *abuf, int filerow);
void	display_tilde(t_env *env, t_abuf *abuf, int n);
void	display_welcome_message(t_env *env, t_abuf *abuf);
void	set_status_message(t_env *env, const char *format, ...);
// --------------------------------------------------------- row_operations.c --
void	insert_row(t_env *env, char *str, size_t len, int index);
int		row_cx_to_rx(t_erow *row, int cx);
void	row_delete_char(t_erow *row, int index, int *dirty);
void	row_insert_char(t_erow *row, int c, int index);
void	update_row(t_erow *row);
// ------------------------------------------------------- row_operations_2.c --
void	delete_row(t_env *env, int index);
void	render_tab(char *render, int *index);
void	row_append_string(t_erow *row, char *s, size_t len, int *dirty);
int		row_rx_to_cx(t_erow *row, int rx);
// --------------------------------------------------------------- terminal.c --
void	enable_raw_mode(void);
int		read_key(void);
int		get_window_size(int *rows, int *cols);
// ------------------------------------------------------------- terminal_2.c --
int		get_cursor_position(int *rows, int *cols);
int		read_escape_sequences(void);
// ------------------------------------------------------------- terminal_3.c --
int		get_nav_key(char *seq);

#endif /* EVE_H */
