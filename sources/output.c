/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:08:14 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/18 13:03:16 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	editor_draw_rows(t_env *env)
{
	int	n;

	n = 0;
	while (n < env->screenrows)
	{
		write(STDOUT_FILENO, "~", 1);
		if (n++ < env->screenrows - 1)
			write(STDOUT_FILENO, "\r\n", 2);
	}
}

void	editor_refresh_screen(t_env *env)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	editor_draw_rows(env);
	write(STDOUT_FILENO, "\x1b[H", 3);
}
