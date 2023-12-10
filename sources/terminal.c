/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:25:14 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/10 23:58:27 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

struct termios	g_orig_termios;

void	disable_raw_mode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, \
	&g_orig_termios) == -1)
		die("tcsetattr s_orig_termios");
}

void	enable_raw_mode(void)
{
	struct termios	s_raw;

	if (tcgetattr(STDIN_FILENO, &g_orig_termios) == -1)
		die("tcgetattr s_orig_termios");
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

int	read_key(int *pi, char *pc)
{
	int	i;

	i = read(STDIN_FILENO, pc, 1);
	*pi = i;
	return (i);
}

char	editor_read_key(void)
{
	int		rread;
	char	c;

	while (read_key(&rread, &c) != 1)
		if (rread == -1 && errno != EAGAIN)
			die("read");
	return (c);
}

int	get_window_size(int *rows, int *cols)
{
	struct winsize	s_ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &s_ws) == -1 \
	|| s_ws.ws_col == 0)
		return (-1);
	else
	{
		*rows = s_ws.ws_row;
		*cols = s_ws.ws_col;
	}
	return (0);
}
