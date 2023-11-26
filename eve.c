/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eve.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:20:29 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/26 13:29:22 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	atexit(disable_raw_mode);
	tcgetattr(STDIN_FILENO, &g_orig_termios);
	raw = g_orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int	main(void)
{
	char	c;

	enable_raw_mode();
	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q')
	{
	}
	return (0);
}
