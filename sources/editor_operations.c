/* ************************************************************************** */
/*                                                                            */
/*   editor_operations.c - functions called from process_keypress()           */
/*                                                                            */
/*   Created: 2024/07/22 11:54:00 by cezelot                                  */
/*   Updated: 2024/07/22 17:19:36 by cezelot                                  */
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

#include "../includes/eve.h"

/* Insert the character C at the current position of the cursor,
   then move the cursor forward.  */
void	insert_char(t_env *env, int c)
{
	if (env->cy == env->numrows)
		append_row(env, "", 0);
	row_insert_char(&env->row[env->cy], c, env->cx);
	env->cx++;
	env->dirty++;
}

/* Delete the character that is to the left of the cursor.  */
void	delete_char(t_env *env)
{
	t_erow	*row;

	if (env->cy == env->numrows)
		return ;
	if (env->cy == 0 && env->cx == 0)
		return ;
	row = &env->row[env->cy];
	if (env->cx > 0)
	{
		row_delete_char(row, env->cx - 1, &env->dirty);
		env->cx--;
	}
	else
	{
		env->cx = env->row[env->cy - 1].size;
		row_append_string(&env->row[env->cy - 1], row->chars, \
						row->size, &env->dirty);
		delete_row(env, env->cy);
		env->cy--;
	}
}
