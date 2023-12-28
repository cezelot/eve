/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:32:33 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/28 14:03:43 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	editor_move_cursor(t_env *env, int key)
{
	if (key == ARROW_LEFT)
		if (env->cx != 0)
			env->cx--;
	if (key == ARROW_RIGHT)
		if (env->cx != env->screencols - 1)
			env->cx++;
	if (key == ARROW_UP)
		if (env->cy != 0)
			env->cy--;
	if (key == ARROW_DOWN)
		if (env->cy != env->screenrows - 1)
			env->cy++;
}

void	editor_process_keypress(t_env *env)
{
	int	c;

	c = editor_read_key();
	if (c == ('q' & 0x1f))
	{
		write(STDOUT_FILENO, "\x1b[2J", 4);
		write(STDOUT_FILENO, "\x1b[H", 3);
		exit(0);
	}
	else if ((c == ARROW_LEFT) || (c == ARROW_RIGHT) \
			|| (c == ARROW_UP) || (c == ARROW_DOWN))
		editor_move_cursor(env, c);
}
