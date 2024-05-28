/* ************************************************************************** */
/*                                                                            */
/*   terminal.c                                                     .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/11/27 18:25:14 by cezelot                     d8P.a8P      */
/*   Updated: 2024/03/25 19:45:04 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

struct termios	g_orig_termios;

void	die(const char *str)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	perror(str);
	exit(1);
}

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

void	disable_raw_mode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, \
	&g_orig_termios) == -1)
		die("tcsetattr g_orig_termios");
}

void	enable_raw_mode(void)
{
	struct termios	s_raw;

	if (tcgetattr(STDIN_FILENO, &g_orig_termios) == -1)
		die("tcgetattr g_orig_termios");
	s_raw = g_orig_termios;
	s_raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	s_raw.c_oflag &= ~(OPOST);
	s_raw.c_cflag |= (CS8);
	s_raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	s_raw.c_cc[VMIN] = 0;
	s_raw.c_cc[VTIME] = 1;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &s_raw) == -1)
		die("tcsetattr s_raw");
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
			die("editor_read_key nbytes_read");
	}
	if (c == '\x1b')
		return (read_escape_sequences());
	else
		return (c);
}
