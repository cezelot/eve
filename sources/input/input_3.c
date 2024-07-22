/* ************************************************************************** */
/*                                                                            */
/*   input_3.c                                                                */
/*                                                                            */
/*   Created: 2024/05/30 17:10:05 by cezelot                                  */
/*   Updated: 2024/07/22 14:08:32 by cezelot                                  */
/*                                                                            */
/*   Copyright (C) 2024 Ismael B. Hamed, Alberto Rodriguez                    */
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

static inline int	handle_special_keys(t_env *env, int key)
{
	switch (key)
	{
		case HOME_KEY:
			env->cx = 0;
			return (1);
		case END_KEY:
			move_cursor_to_end_line(env);
			return (1);
		case BACKSPACE:
		case ('h' & 0x1f):
		case DEL_KEY:
			if (key == DEL_KEY)
				editor_move_cursor(env, ARROW_RIGHT);
			editor_del_char(env);
			return (1);
		case ('l' & 0x1f):
		case '\x1b':
			return (1);
		default:
			return (0);
	}
}

static inline int	handle_page_keys(t_env *env, int key)
{
	if (is_page_keys(key))
	{
		process_page_keys(env, key);
		return (1);
	}
	return (0);
}

static inline int	handle_movement_keys(t_env *env, int key)
{
	if (is_arrow_keys(key))
	{
		editor_move_cursor(env, key);
		return (1);
	}
	return (0);
}

static inline int	handle_navigation_keys(t_env *env, int key)
{
	if (handle_page_keys(env, key))
		return (1);
	if (handle_movement_keys(env, key))
		return (1);
	return (0);
}

void	process_esc_seq_keys(t_env *env, int key)
{
	if (handle_special_keys(env, key))
		return ;
	if (handle_navigation_keys(env, key))
		return ;
	editor_insert_char(env, key);
}
