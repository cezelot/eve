/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:32:33 by bhamed            #+#    #+#             */
/*   Updated: 2024/01/01 19:14:26 by bhamed           ###   ########.fr       */
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
		if (env->cy < env->numrows)
			env->cy++;
}

void	process_esc_seq_keys(int c, t_env *env)
{
	int	times;

	times = env->screenrows;
	if (c == HOME_KEY)
		env->cx = 0;
	else if (c == END_KEY)
		env->cx = env->screencols - 1;
	else if ((c == PAGE_UP) || (c == PAGE_DOWN))
	{
		while (times--)
		{
			if (c == PAGE_UP)
				editor_move_cursor(env, ARROW_UP);
			else
				editor_move_cursor(env, ARROW_DOWN);
		}
	}
	else if ((c == ARROW_LEFT) || (c == ARROW_RIGHT) \
			|| (c == ARROW_UP) || (c == ARROW_DOWN))
		editor_move_cursor(env, c);
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
	else
		process_esc_seq_keys(c, env);
}
