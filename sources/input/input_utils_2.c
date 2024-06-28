/* ************************************************************************** */
/*                                                                            */
/*   input_utils_2.c                                                          */
/*                                                                            */
/*   Created: 2024/05/30 17:10:05 by cezelot.                                 */
/*   Updated: 2024/05/31 20:26:10 by cezelot.                                 */
/*                                                                            */
/*   Copyright 2024 cezelot.                                                  */
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

void	change_page(t_env *env, int c)
{
	int	times;

	times = env->screenrows;
	while (times--)
	{
		if (c == PAGE_UP)
			editor_move_cursor(env, ARROW_UP);
		else
			editor_move_cursor(env, ARROW_DOWN);
	}
}

void	move_cursor_to_end_line(t_env *env)
{
	if (env->cy < env->numrows)
		env->cx = env->row[env->cy].size;
}

int	is_arrow_keys(int c)
{
	return ((c == ARROW_LEFT) || (c == ARROW_RIGHT) || \
	(c == ARROW_UP) || (c == ARROW_DOWN));
}

int	is_page_keys(int c)
{
	return ((c == PAGE_UP) || (c == PAGE_DOWN));
}
