/* ************************************************************************** */
/*                                                                            */
/*   row_operations.c                                                         */
/*                                                                            */
/*   Created: 2023/12/31 18:08:27 by cezelot                                  */
/*   Updated: 2024/07/23 19:07:08 by cezelot                                  */
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

/* Converts a chars index into a render index,
   and return the render index.  */
int
row_cx_to_rx(t_erow *row, int cx)
{
	int	rx = 0;
	int	i = 0;

	while (i < cx) {
		if (row->chars[i++] == '\t') {
			rx += (TAB_STOP - 1) - (rx % TAB_STOP);
		}
		++rx;
	}
	return (rx);
}

/* Update RENDER and RSIZE according to CHARS.  */
void
update_row(t_erow *row)
{
	int	i = 0;
	int	n = 0;
	int	tabs = 0;

	while (n < row->size) {
		if (row->chars[n++] == '\t') {
			++tabs;
		}
	}
	free(row->render);
	row->render = malloc(row->size + tabs * (TAB_STOP - 1) + 1);
	if (row->render == NULL) {
		die("%s:%d: %s: please go buy a RAM upgrade "
			"from your local plug",
			__FILE__, __LINE__, strerror(errno));
	}
	n = 0;
	while (n < row->size) {
		if (row->chars[n] == '\t') {
			render_tab(row->render, &i);
		} else {
			row->render[i++] = row->chars[n];
		}
		++n;
	}
	row->render[i] = '\0';
	row->rsize = i;
}

/* Insert the character C into CHARS, at position INDEX,
   and update the other variables in row.  */
void
row_insert_char(t_erow *row, int c, int index)
{
	if (index < 0 || index > row->size) {
		index = row->size;
	}
	row->chars = realloc(row->chars, row->size + 2);
	if (row->chars == NULL) {
		return ;
	}
	memmove(&row->chars[index + 1], &row->chars[index], row->size - index + 1);
	row->size++;
	row->chars[index] = c;
	update_row(row);
}

/* Copy STR to a new row, then insert the row at INDEX.  */
void
insert_row(t_env *env, char *str, size_t len, int index)
{
	if (index < 0 || index > env->numrows) {
		return ;
	}
	env->row = realloc(env->row, (env->numrows + 1) * sizeof(t_erow));
	if (env->row == NULL) {
		return ;
	}
	memmove(&env->row[index + 1], &env->row[index],
		(env->numrows - index) * sizeof(t_erow));
	env->row = realloc(env->row, (env->numrows + 1) * sizeof(t_erow));
	if (env->row == NULL) {
		return ;
	}
	env->row[index].size = len;
	env->row[index].chars = malloc(len + 1);
	if (env->row[index].chars == NULL) {
		die("%s:%d: Hot Damn! You need more ram!", __FILE__, __LINE__);
	}
	memcpy(env->row[index].chars, str, len);
	env->row[index].chars[len] = '\0';
	env->row[index].rsize = 0;
	env->row[index].render = NULL;
	update_row(&env->row[index]);
	env->numrows++;
	env->dirty++;
}

/* Delete the character at INDEX in ROW, then increment DIRTY.  */
void
row_delete_char(t_erow *row, int index, int *dirty)
{
	if (index < 0 || index >= row->size) {
		return ;
	}
	memmove(&row->chars[index], &row->chars[index + 1], row->size - index);
	row->size--;
	update_row(row);
	++*dirty;
}
