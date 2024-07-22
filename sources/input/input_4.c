/* ************************************************************************** */
/*                                                                            */
/*   input_4.c                                                                */
/*                                                                            */
/*   Created: 2024/07/11 16:56:07 by cezelot                                  */
/*   Updated: 2024/07/21 16:50:15 by cezelot                                  */
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

void	move_cursor_to_end_line(t_env *env)
{
	if (env->cy < env->numrows)
		env->cx = env->row[env->cy].size;
}

int	is_arrow_keys(int key)
{
	return ((key == ARROW_LEFT) || (key == ARROW_RIGHT) \
			|| (key == ARROW_UP) || (key == ARROW_DOWN));
}

int	is_page_keys(int key)
{
	return ((key == PAGE_UP) || (key == PAGE_DOWN));
}

static void	change_page(t_env *env, int key)
{
	int	times;

	times = env->screenrows;
	while (times--)
	{
		if (key == PAGE_UP)
			move_cursor(env, ARROW_UP);
		else
			move_cursor(env, ARROW_DOWN);
	}
}

void	process_page_keys(t_env *env, int key)
{
	if (key == PAGE_UP)
		env->cy = env->rowoff;
	else
	{
		env->cy = env->rowoff + env->screenrows - 1;
		if (env->cy > env->numrows)
			env->cy = env->numrows;
	}
	change_page(env, key);
}
