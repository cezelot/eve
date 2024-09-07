/* ************************************************************************** */
/*                                                                            */
/*   editor_operations.c - functions called from process_keypress()           */
/*                                                                            */
/*   Created: 2024/07/22 11:54:00 by cezelot                                  */
/*   Updated: 2024/09/07 18:36:33 by cezelot                                  */
/*                                                                            */
/*   Copyright (C) 2024 Ismael Benjara                                        */
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

#include "eve.h"

/* Insert the character C at the current position of the cursor,
   then move the cursor forward.  */
void
insert_char(t_env *env, int c)
{
	if (env->cy == env->numrows) {
		insert_row(env, "", 0, env->numrows);
	}
	row_insert_char(env, &env->row[env->cy], c);
	env->cx++;
	env->dirty++;
}

/* Insert a new line at the current position of the cursor,
   then move the cursor to the beginning of that line.  */
void
insert_newline(t_env *env)
{
	t_erow	*row;

	row = &env->row[env->cy];
	if (env->cx != 0) {
		insert_row(env, &row->chars[env->cx],
			row->size - env->cx, env->cy + 1);
		row = &env->row[env->cy];
		row->size = env->cx;
		row->chars[row->size] = '\0';
		update_row(env, row);
	} else {
		insert_row(env, "", 0, env->cy);
	}
	env->cy++;
	env->cx = 0;
}

/* Delete the character that is to the left of the cursor.  */
void
delete_char(t_env *env)
{
	t_erow	*row;

	if (env->cy == env->numrows) {
		return ;
	}
	if (env->cy == 0 && env->cx == 0) {
		return ;
	}
	row = &env->row[env->cy];
	if (env->cx > 0) {
		row_delete_char(env, row);
		env->cx--;
	} else {
		env->cx = env->row[env->cy - 1].size;
		row_append_string(env, row->chars, row->size);
		delete_row(env, env->cy);
		env->cy--;
	}
}
