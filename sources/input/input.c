/* ************************************************************************** */
/*                                                                            */
/*   input.c - map keypresses to editor functions                             */
/*                                                                            */
/*   Created: 2023/11/27 18:32:33 by cezelot                                  */
/*   Updated: 2024/07/12 19:27:44 by cezelot                                  */
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
void	editor_move_cursor(t_env *env, int key)
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

static void	process_page_keys(t_env *env, int c)
{
	if (c == PAGE_UP)
		env->cy = env->rowoff;
	else
	{
		env->cy = env->rowoff + env->screenrows - 1;
		if (env->cy > env->numrows)
			env->cy = env->numrows;
	}
	change_page(env, c);
}

static void	process_esc_seq_keys(t_env *env, int c)
{
	if (c == HOME_KEY)
		env->cx = 0;
	else if (c == END_KEY)
		move_cursor_to_end_line(env);
	else if (c == BACKSPACE || c == ('h' & 0x1f) || c == DEL_KEY)
		/* To-Do */
		return ;
	else if (is_page_keys(c))
		process_page_keys(env, c);
	else if (is_arrow_keys(c))
		editor_move_cursor(env, c);
	else if (c == ('l' & 0x1f) || c == '\x1b')
		return ;
	else
		editor_insert_char(env, c);
}

/* Wait for a keypress, then handle it.  */
void	editor_process_keypress(t_env *env)
{
	int	c;

	c = editor_read_key();
	if (c == '\r')
		/* To-Do */
		return ;
	if (c == ('q' & 0x1f))
	{
		write(STDOUT_FILENO, "\x1b[2J", 4);
		write(STDOUT_FILENO, "\x1b[H", 3);
		close_editor(env);
		exit(0);
	}
	else
		process_esc_seq_keys(env, c);
}
