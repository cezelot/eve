/* ************************************************************************** */
/*                                                                            */
/*   input_4.c                                                                */
/*                                                                            */
/*   Created: 2024/07/11 16:56:07 by cezelot                                  */
/*   Updated: 2024/08/17 18:47:48 by alberrod                                 */
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

#include "../eve.h"

void
move_cursor_to_end_line(t_env *env)
{
	if (env->cy < env->numrows) {
		env->cx = env->row[env->cy].size;
	}
}

void
change_page(t_env *env, int key)
{
	int	times = env->screenrows;

	while (times--) {
		if (key == PAGE_UP) {
			move_cursor(env, ARROW_UP);
		} else {
			move_cursor(env, ARROW_DOWN);
		}
	}
}

void
quit_program(t_env *env)
{
	if (env->dirty && env->quit_times > 0) {
		set_status_message(env, "File has unsaved changes! "
			"Press 'Ctrl-Q' one more time to quit");
		--env->quit_times;
		return ;
	}
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	close_editor(env);
	exit(0);
}
