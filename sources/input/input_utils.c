/* ************************************************************************** */
/*                                                                            */
/*   input_utils.c                                                            */
/*                                                                            */
/*   Created: 2024/05/28 10:13:12 by cezelot                                  */
/*   Updated: 2024/05/30 21:00:44 by cezelot                                  */
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

void	snap_cursor_to_end_line(t_env *env, t_erow *row, int rowlen)
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

void	move_cursor_down(t_env *env)
{
	if (env->cy < env->numrows)
		env->cy++;
}

void	move_cursor_up(t_env *env)
{
	if (env->cy != 0)
		env->cy--;
}

void	move_cursor_right(t_env *env, t_erow *row)
{
	if (row && env->cx < row->size)
		env->cx++;
	else if (row && env->cx == row->size)
	{
		env->cy++;
		env->cx = 0;
	}
}

void	move_cursor_left(t_env *env)
{
	if (env->cx != 0)
		env->cx--;
	else if (env->cy > 0)
	{
		env->cy--;
		env->cx = env->row[env->cy].size;
	}
}
