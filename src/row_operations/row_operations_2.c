/* ************************************************************************** */
/*                                                                            */
/*   row_operations_2.c                                                       */
/*                                                                            */
/*   Created: 2024/07/22 11:34:50 by cezelot                                  */
/*   Updated: 2024/07/27 14:50:42 by cezelot                                  */
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

#include "../eve.h"

/* Converts a render index into a chars index,
   and return the chars index.  */
int
row_rx_to_cx(t_erow *row, int rx)
{
	int	cur_rx = 0;
	int	cx = 0;

	while (cx < row->size) {
		if (row->chars[cx] == '\t') {
			cur_rx += (TAB_STOP - 1) - (cur_rx % TAB_STOP);
		}
		++cur_rx;
		if (cur_rx > rx) {
			return (cx);
		}
		++cx;
	}
	return (cx);
}

/* Replace a tab by TAB_STOP spaces characters.  */
void
render_tab(char *render, int *index)
{
	render[(*index)++] = ' ';
	while (*index % TAB_STOP) {
		render[(*index)++] = ' ';
	}
}

/* Append S to the end of ROW.  */
void
row_append_string(t_erow *row, char *s, size_t len, int *dirty)
{
	row->chars = realloc(row->chars, row->size + len + 1);
	memcpy(&row->chars[row->size], s, len);
	row->size += len;
	row->chars[row->size] = '\0';
	update_row(row);
	++*dirty;
}

/* Deallocate memories in ROW.  */
static void
free_row(t_erow *row)
{
	free(row->render);
	free(row->chars);
}

/* Delete ROW at INDEX.  */
void
delete_row(t_env *env, int index)
{
	if (index < 0 || index >= env->numrows) {
		return ;
	}
	free_row(&env->row[index]);
	memmove(&env->row[index], &env->row[index + 1],
		(env->numrows - index - 1) * sizeof(t_erow));
	env->numrows--;
	env->dirty++;
}
