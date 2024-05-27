/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:32:33 by bhamed            #+#    #+#             */
/*   Updated: 2024/05/27 14:21:22 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

static void	snap_cursor_to_end_of_line(t_env *env, t_erow *row, int rowlen)
{
	if (env->cy >= env->numrows)
		row = NULL;
	else
		row = &env->row[env->cy];
	if (row)
		rowlen = row->size;
	else
		row = 0;
	if (env->cx > rowlen)
		env->cx = rowlen;
}

static void	editor_move_cursor(t_env *env, int key)
{
	t_erow	*row;
	int		rowlen;

	rowlen = 0;
	if (env->cy >= env->numrows)
		row = NULL;
	else
		row = &env->row[env->cy];
	if (key == ARROW_LEFT)
		if (env->cx != 0)
			env->cx--;
	if (key == ARROW_RIGHT)
		if (row && env->cx < row->size)
			env->cx++;
	if (key == ARROW_UP)
		if (env->cy != 0)
			env->cy--;
	if (key == ARROW_DOWN)
		if (env->cy < env->numrows)
			env->cy++;
	snap_cursor_to_end_of_line(env, row, rowlen);
}

static void	process_esc_seq_keys(int c, t_env *env)
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
