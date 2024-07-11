/* ************************************************************************** */
/*                                                                            */
/*   input_utils_3.c - functions called from editor_process_keypress()        */
/*                                                                            */
/*   Created: 2024/07/11 16:56:07 by cezelot                                  */
/*   Updated: 2024/07/11 17:21:02 by cezelot                                  */
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

/* Insert the character C at the current position of the cursor,
   then move the cursor forward.  */
void	editor_insert_char(t_env *env, int c)
{
	if (env->cy == env->numrows)
		editor_append_row(env, "", 0);
	editor_row_insert_char(&env->row[env->cy], c, env->cx);
	env->cx++;
}
