/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:25:14 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/27 18:50:46 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

struct termios	g_orig_termios;

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

char	editor_read_key(void)
{
	int		nread;
	char	c;

	while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
		if (nread == -1 && errno != EAGAIN)
			die("read");
	return (c);
}
