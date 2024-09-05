/* ************************************************************************** */
/*                                                                            */
/*   find.c - search routines                                                 */
/*                                                                            */
/*   Created: 2024/07/27 14:14:36 by cezelot                                  */
/*   Updated: 2024/09/05 14:41:07 by cezelot                                  */
/*                                                                            */
/*   Copyright (C) 2024 Ismael Benjara                                        */
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

#include "eve.h"

/* Loop through all the rows of the file to check
   if a row contains QUERY.  If there is a match,
   move the cursor to the match.  */
static void
find_callback(t_env *env, char *query, int key)
{
	t_erow		*row;
	char		*match;
	int		i = 0;
	/* Index of the row that the last match was on,
	   or -1 if there was no last match.  */
	static int	last_match = -1;
	/* Direction of the search: 1 for searching forward,
	   and -1 for searching backward.  */
	static int	direction = 1;
	/* Index of the current row we are searching.  */
	int		current;
	static int	saved_hl_line;
	static char	*saved_hl = NULL;

	if (saved_hl) {
		memcpy(env->row[saved_hl_line].hl, saved_hl,
			env->row[saved_hl_line].rsize);
		free(saved_hl);
		saved_hl = NULL;
	}
	if (key == ARROW_RIGHT || key == ARROW_DOWN) {
		direction = 1;
	} else if (key == ARROW_LEFT || key == ARROW_UP) {
		direction = -1;
	} else if (key == NEWLINE_KEY || key == ESC) {
		/* Reset LAST_MATCH and DIRECTION to their initial values
		   to get ready for the next search operation.  */
		last_match = -1;
		direction = 1;
		return ;
	} else {
		last_match = -1;
		direction = 1;
	}
	if (last_match == -1) {
		direction = 1;
	}
	current = last_match;
	while (i < env->numrows) {
		current += direction;
		/* Wrap around the end of a file and
		   continue from the top (or bottom).  */
		if (current == -1) {
			current = env->numrows - 1;
		} else if (current == env->numrows) {
			current = 0;
		}
		row = &env->row[current];
		match = strstr(row->render, query);
		if (match) {
			last_match = current;
			env->cy = current;
			env->cx = row_rx_to_cx(row, match - row->render);
			env->rowoff = env->numrows;
			saved_hl_line = current;
			saved_hl = malloc(row->rsize);
			memcpy(saved_hl, row->hl, row->rsize);
			memset(&row->hl[match - row->render],
				HL_MATCH, strlen(query));
			break ;
		}
		++i;
	}
}

void
find(t_env *env)
{
	char	*query;
	int	last_cy = env->cy;
	int	last_cx = env->cx;
	int	last_coloff = env->coloff;
	int	last_rowoff = env->rowoff;

	query = prompt(env, "Search: %s", find_callback);
	if (query == NULL) {
		env->cy = last_cy;
		env->cx = last_cx;
		env->coloff = last_coloff;
		env->rowoff = last_rowoff;
	} else {
		free(query);
	}
}
