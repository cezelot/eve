/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eve.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:20:29 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/26 19:29:45 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/* data */

struct termios	g_orig_termios;

/* terminal */

void	die(const char *str)
{
	perror(str);
	exit(1);
}

void	disable_raw_mode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_orig_termios) == -1)
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

/* init */

int	main(void)
{
	char	c;

	enable_raw_mode();
	atexit(disable_raw_mode);
	while (1)
	{
		c = '\0';
		if (read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
			die ("read");
		if (iscntrl(c))
			printf("%d\r\n", c);
		else
			printf("%d (%c)\r\n", c, c);
		if (c == (('q') & 0x1f))
			break ;
	}
	return (0);
}
