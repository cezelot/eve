/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:35:43 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/28 13:42:31 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

int	read_escape_sequences(void)
{
	char	seq[3];

	if (read(STDIN_FILENO, &seq[0], 1) != 1)
		return ('\x1b');
	if (read(STDIN_FILENO, &seq[1], 1) != 1)
		return ('\x1b');
	if (seq[0] == '[')
	{
		if (seq[1] == 'A')
			return (ARROW_UP);
		else if (seq[1] == 'B')
			return (ARROW_DOWN);
		else if (seq[1] == 'C')
			return (ARROW_RIGHT);
		else if (seq[1] == 'D')
			return (ARROW_LEFT);
	}
	return ('\x1b');
}

int	get_cursor_position(int *rows, int *cols)
{
	char			buf[32];
	unsigned int	i;

	i = 0;
	if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
		return (-1);
	while (i < sizeof(buf) - 1)
	{
		if (read(STDIN_FILENO, &buf[i], 1) != 1)
			break ;
		if (buf[i] == 'R')
			break ;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] != '\x1b' || buf[1] != '[')
		return (-1);
	if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
		return (-1);
	return (0);
}

int	get_window_size(int *rows, int *cols)
{
	struct winsize	s_ws;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &s_ws) == -1 \
	|| s_ws.ws_col == 0)
	{
		if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
			return (-1);
		return (get_cursor_position(rows, cols));
	}
	else
	{
		*rows = s_ws.ws_row;
		*cols = s_ws.ws_col;
		return (0);
	}
}
