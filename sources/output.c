/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:08:14 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/10 17:49:44 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	editor_draw_rows(void)
{
	int	n;

	n = 0;
	while (n++ < 24)
		write(STDOUT_FILENO, "~\r\n", 3);
}

void	editor_refresh_screen(void)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	editor_draw_rows();
	write(STDOUT_FILENO, "\x1b[H", 3);
}
