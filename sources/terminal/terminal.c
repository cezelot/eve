/* ************************************************************************** */
/*                                                                            */
/*   terminal.c                                                               */
/*                                                                            */
/*   Created: 2023/11/27 18:25:14 by cezelot.                                 */
/*   Updated: 2024/07/02 12:23:09 by cezelot.                                 */
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

#include "../../includes/eve.h"

struct termios	g_orig_termios;

int	get_window_size(int *rows, int *cols)
{
	struct winsize	ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 \
	|| ws.ws_col == 0)
	{
		if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
			return (-1);
		return (get_cursor_position(rows, cols));
	}
	else
	{
		*rows = ws.ws_row;
		*cols = ws.ws_col;
		return (0);
	}
}

static void	disable_raw_mode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_orig_termios) == -1)
		die("%s:%d: unable to restore terminal’s original attributes: %s", \
			__FILE__, __LINE__, strerror(errno));
}

void	enable_raw_mode(void)
{
	struct termios	s_raw;

	if (tcgetattr(STDIN_FILENO, &g_orig_termios) == -1)
		die("%s:%d: unable to get terminal attributes: %s", \
			__FILE__, __LINE__, strerror(errno));
	atexit(disable_raw_mode);
	s_raw = g_orig_termios;
	s_raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	s_raw.c_oflag &= ~(OPOST);
	s_raw.c_cflag |= (CS8);
	s_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	s_raw.c_cc[VMIN] = 0;
	s_raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &s_raw) == -1)
		die("%s:%d: unable to set terminal attributes: %s", \
			__FILE__, __LINE__, strerror(errno));
}

int	editor_read_key(void)
{
	ssize_t	nbytes_read;
	char	c;

	while (1)
	{
		nbytes_read = read(STDIN_FILENO, &c, 1);
		if (nbytes_read == 1)
			break ;
		if (nbytes_read == -1 && errno != EAGAIN)
			die("%s:%d: unable to read key pressed: %s", \
				__FILE__, __LINE__, strerror(errno));
	}
	if (c == '\x1b')
		return (read_escape_sequences());
	else
		return (c);
}
