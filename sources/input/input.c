/* ************************************************************************** */
/*                                                                            */
/*   input.c - map keypresses to editor functions                             */
/*                                                                            */
/*   Created: 2023/11/27 18:32:33 by cezelot                                  */
/*   Updated: 2024/07/23 19:29:49 by cezelot                                  */
/*                                                                            */
/*   Copyright (C) 2024 Ismael B. Hamed                                       */
/*                                                                            */
/*   This file is part of eve.                                                */
/*                                                                            */
/*   eve is free software: you can redistribute it and/or modify              */
/*   it under the terms of the GNU General Public License as published by     */
/*   the Free Software Foundation, either version 3 of the License, or        */
/*   (at your option) any later version.                                      */
/*                                                                            */
/*   eve is distributed in the hope that it will be useful,                   */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*   GNU General Public License for more details.                             */
/*                                                                            */
/*   You should have received a copy of the GNU General Public License        */
/*   along with eve.  If not, see <https://www.gnu.org/licenses/>.            */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

/* Move the cursor according to the given key.  */
void	move_cursor(t_env *env, int key)
{
	t_erow	*row;
	int		rowlen;

	rowlen = 0;
	if (env->cy >= env->numrows)
		row = NULL;
	else
		row = &env->row[env->cy];
	if (key == ARROW_LEFT)
		move_cursor_left(env);
	if (key == ARROW_RIGHT)
		move_cursor_right(env, row);
	if (key == ARROW_UP)
		move_cursor_up(env);
	if (key == ARROW_DOWN)
		move_cursor_down(env);
	snap_cursor_to_end_line(env, row, rowlen);
}

/* Wait for a keypress, then handle it.  */
void	process_keypress(t_env *env)
{
	static int	quit_times = 1;
	int			key;

	key = read_key();
	if (key == '\r')
	{
		insert_newline(env);
		return ;
	}
	if (key == ('q' & 0x1f))
	{
		if (env->dirty && quit_times > 0)
		{
			set_status_message(env, \
			"File has unsaved changes! Press 'Ctrl-Q' one more time to quit");
			--quit_times;
			return ;
		}
		write(STDOUT_FILENO, "\x1b[2J", 4);
		write(STDOUT_FILENO, "\x1b[H", 3);
		close_editor(env);
		exit(0);
	}
	if (key == ('s' & 0x1f))
		save(env);
	else
		process_esc_seq_keys(env, key);
	quit_times = 1;
}
