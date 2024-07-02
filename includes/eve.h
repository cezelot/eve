/* ************************************************************************** */
/*                                                                            */
/*   eve.h                                                                    */
/*                                                                            */
/*   Created: 2023/11/27 17:17:10 by cezelot.                                 */
/*   Updated: 2024/07/02 12:10:46 by cezelot.                                 */
/*                                                                            */
/*   Copyright 2024 cezelot.                                                  */
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
# define EVE_TAB_STOP 4
# define EVE_VERSION "0.1.0"
# define PROGRAM_NAME "eve"

# include <ctype.h>
# include <errno.h>
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

typedef struct s_erow
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
	char	statusmsg[80];
	time_t	statusmsg_time;
}			t_env;

typedef struct s_abuf
{
	char	*buf;
	int		len;
}			t_abuf;

// ------------------------------------------------------------------- main.c --
void	close_editor(t_env *env);
void	die(const char *format, ...);
// ---------------------------------------------------------------- options.c --
void	parse_options(int ac, char **av, int *option_index);
// ------------------------------------------------------------------ input.c --
void	editor_move_cursor(t_env *env, int key);
void	editor_process_keypress(t_env *env);
// ------------------------------------------------------------ input_utils.c --
void	move_cursor_down(t_env *env);
void	move_cursor_left(t_env *env);
void	move_cursor_right(t_env *env, t_erow *row);
void	move_cursor_up(t_env *env);
void	snap_cursor_to_end_line(t_env *env, t_erow *row, int rowlen);
// ---------------------------------------------------------- input_utils_2.c --
void	change_page(t_env *env, int c);
int		is_arrow_keys(int c);
int		is_page_keys(int c);
void	move_cursor_to_end_line(t_env *env);
// --------------------------------------------------------------- terminal.c --
void	enable_raw_mode(void);
int		editor_read_key(void);
// --------------------------------------------------------- terminal_utils.c --
int		get_cursor_position(int *rows, int *cols);
int		get_window_size(int *rows, int *cols);
int		read_escape_sequences(void);
// ------------------------------------------------------- terminal_utils_2.c --
int		get_nav_key(char *seq);
// ----------------------------------------------------------------- output.c --
void	editor_draw_message_bar(t_env *env, t_abuf *abuf);
void	editor_refresh_screen(t_env *env);
// ----------------------------------------------------------- output_utils.c --
void	display_text_buffer(t_env *env, t_abuf *abuf, int filerow);
void	display_tilde(t_env *env, t_abuf *abuf, int n);
void	display_welcome_message(t_env *env, t_abuf *abuf);
void	editor_set_status_message(t_env *env, const char *format, ...);
// ---------------------------------------------------------- append_buffer.c --
void	abuf_append(t_abuf *abuf, const char *str, int len);
void	abuf_free(t_abuf *abuf);
// ---------------------------------------------------------------- file_io.c --
void	editor_open(t_env *env, char *filename);
// --------------------------------------------------------- row_operations.c --
void	editor_append_row(t_env *env, char *str, size_t len);
int		editor_row_cx_to_rx(t_erow *row, int cx);

#endif
