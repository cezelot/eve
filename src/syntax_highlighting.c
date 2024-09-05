/* ************************************************************************** */
/*                                                                            */
/*   syntax_highlighting.c                                                    */
/*                                                                            */
/*   Created: 2024/09/01 15:58:19 by cezelot                                  */
/*   Updated: 2024/09/05 16:56:43 by cezelot                                  */
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

static int
is_separator(int c)
{
	return (isspace(c) || c == '\0'
		|| strchr(",.()+-/*=~%<>[];", c) != NULL);
}

/* Highlight the characters of ROW.  */
void
update_syntax(t_erow *row)
{
	char		c;
	unsigned char	prev_hl;
	int		prev_sep = 0;
	int		i = 0;

	row->hl = realloc(row->hl, row->rsize);
	if (row->hl == NULL)
		return ;
	memset(row->hl, HL_NORMAL, row->rsize);
	while (i < row->rsize) {
		c = row->render[i];
		if (i > 0) {
			prev_hl = row->hl[i - 1];
		} else {
			prev_hl = HL_NORMAL;
		}
		if ((isdigit(c) && (prev_sep || prev_hl == HL_NUMBER))
				|| (c == '.' && prev_hl == HL_NUMBER)) {
			row->hl[i] = HL_NUMBER;
			++i;
			prev_sep = 0;
			continue ;
		}
		prev_sep = is_separator(c);
		++i;
	}
}

/* Map values in hl to ANSI color codes.  */
int
syntax_to_color(int hl)
{
	switch (hl) {
	case HL_NUMBER:
		return (31);
	case HL_MATCH:
		return (34);
	default:
		return (37);
	}
}
