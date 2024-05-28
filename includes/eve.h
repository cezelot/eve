/* ************************************************************************** */
/*                                                                            */
/*   eve.h                                                          .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/11/27 17:17:10 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/28 12:51:09 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVE_H
# define EVE_H

# define _DEFAULT_SOURCE
# define EVE_VERSION "0.0.1"
# define EVE_TAB_STOP 4

# include <ctype.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
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
	int		rowoff;
	int		coloff;
	int		screenrows;
	int		screencols;
	int		numrows;
	t_erow	*row;
}			t_env;

typedef struct s_abuf
{
	char	*buf;
	int		len;
}			t_abuf;

// ------------------------------------------------------------------ input.c --
void	editor_process_keypress(t_env *env);
// ------------------------------------------------------------ input_utils.c --
void	move_cursor_down(t_env *env);
void	move_cursor_left(t_env *env);
void	move_cursor_right(t_env *env, t_erow *row);
void	move_cursor_up(t_env *env);
void	snap_cursor_to_end_of_line(t_env *env, t_erow *row, int rowlen);
// --------------------------------------------------------------- terminal.c --
void	die(const char *str);
void	enable_raw_mode(void);
void	disable_raw_mode(void);
int		editor_read_key(void);
// --------------------------------------------------------- terminal_utils.c --
int		get_cursor_position(int *rows, int *cols);
int		get_window_size(int *rows, int *cols);
int		read_escape_sequences(void);
// ----------------------------------------------------------------- output.c --
void	editor_refresh_screen(t_env *env);
// ---------------------------------------------------------- append_buffer.c --
void	abuf_append(t_abuf *abuf, const char *str, int len);
void	abuf_free(t_abuf *abuf);
// ---------------------------------------------------------------- file_io.c --
void	editor_open(t_env *env, char *filename);
// --------------------------------------------------------- row_operations.c --
void	editor_append_row(t_env *env, char *str, size_t len);

#endif
