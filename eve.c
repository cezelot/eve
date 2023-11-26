/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eve.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:20:29 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/26 16:48:26 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios	g_orig_termios;

void	disable_raw_mode(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_orig_termios);
}

void	enable_raw_mode(void)
{
	struct termios	raw;

	tcgetattr(STDIN_FILENO, &g_orig_termios);
	raw = g_orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int	main(void)
{
	char	c;

	enable_raw_mode();
	atexit(disable_raw_mode);
	while (1)
	{
		c = '\0';
		read(STDIN_FILENO, &c, 1);
		if (iscntrl(c))
			printf("%d\r\n", c);
		else
			printf("%d (%c)\r\n", c, c);
		if (c == 'q')
			break ;
	}
	return (0);
}
