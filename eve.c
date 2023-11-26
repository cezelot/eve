/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eve.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:20:29 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/26 13:53:15 by bhamed           ###   ########.fr       */
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
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int	main(void)
{
	char	c;

	enable_raw_mode();
	atexit(disable_raw_mode);
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
	{
		if (iscntrl(c))
			printf("%d\n", c);
		else
			printf("%d (%c)\n", c, c);
	}
	return (0);
}
