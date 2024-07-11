/* ************************************************************************** */
/*                                                                            */
/*   row_operations.c                                                         */
/*                                                                            */
/*   Created: 2023/12/31 18:08:27 by cezelot                                  */
/*   Updated: 2024/07/11 16:54:55 by cezelot                                  */
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

/* Converts a chars index into a render index,
   and return the render index.  */
int	editor_row_cx_to_rx(t_erow *row, int cx)
{
	int	rx;
	int	i;

	rx = 0;
	i = 0;
	while (i < cx)
	{
		if (row->chars[i++] == '\t')
			rx += (EVE_TAB_STOP - 1) - (rx % EVE_TAB_STOP);
		++rx;
	}
	return (rx);
}

/* Replace a tab by EVE_TAB_STOP spaces characters.  */
static void	editor_render_tab(char *render, int *index)
{
	render[(*index)++] = ' ';
	while (*index % EVE_TAB_STOP)
		render[(*index)++] = ' ';
}

/* Update RENDER and RSIZE according to CHARS.  */
static void	editor_update_row(t_erow *row)
{
	int	i;
	int	n;
	int	tabs;

	i = 0;
	n = 0;
	tabs = 0;
	while (n < row->size)
		if (row->chars[n++] == '\t')
			++tabs;
	free(row->render);
	row->render = malloc(row->size + tabs * (EVE_TAB_STOP - 1) + 1);
	n = 0;
	while (n < row->size)
	{
		if (row->chars[n] == '\t')
			editor_render_tab(row->render, &i);
		else
			row->render[i++] = row->chars[n];
		++n;
	}
	row->render[i] = '\0';
	row->rsize = i;
}

/* Insert the character C into CHARS, at position INDEX,
   and update the other variables in row.  */
void	editor_row_insert_char(t_erow *row, int c, int index)
{
	if (index < 0 || index > row->size)
		index = row->size;
	row->chars = realloc(row->chars, row->size + 2);
	memmove(&row->chars[index + 1], &row->chars[index], row->size - index + 1);
	row->size++;
	row->chars[index] = c;
	editor_update_row(row);
}

/* Add STR to the contents of a new editor row,
   and add the new erow after the last erow.  */
void	editor_append_row(t_env *env, char *str, size_t len)
{
	size_t	at;

	env->row = realloc(env->row, sizeof(t_erow) * (env->numrows + 1));
	at = env->numrows;
	env->row[at].size = len;
	env->row[at].chars = malloc(len + 1);
	memcpy(env->row[at].chars, str, len);
	env->row[at].chars[len] = '\0';
	env->row[at].rsize = 0;
	env->row[at].render = NULL;
	editor_update_row(&env->row[at]);
	env->numrows++;
}
