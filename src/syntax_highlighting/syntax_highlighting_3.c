/* ************************************************************************** */
/*                                                                            */
/*   syntax_highlighting_3.c                                                  */
/*                                                                            */
/*   Created: 2024/09/08 10:58:46 by cezelot                                  */
/*   Updated: 2024/10/01 08:42:49 by cezelot                                  */
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

#include "../eve.h"

int
highlight_keyword(t_erow *row, char **keywords, int *i, int *prev_sep)
{
	size_t	n = 0;
	size_t	len;
	size_t	kw2;

	while (keywords[n]) {
		len = strlen(keywords[n]);
		kw2 = keywords[n][len - 1] == '|';
		if (kw2) {
			--len;
		}
		if (!strncmp(&row->render[*i], keywords[n], len)
				&& is_separator(row->render[*i + len])) {
			memset(&row->hl[*i], kw2 ? HL_KEYWORD2 : HL_KEYWORD1,
				len);
			*i += len;
			break ;
		}
		++n;
	}
	if (keywords[n] != NULL) {
		*prev_sep = 0;
		return (1);
	}
	return (0);
}

int
highlight_string(t_erow *row, int *i, int *prev_sep, int *in_string)
{
	char	c = row->render[*i];

	if (*in_string) {
		row->hl[*i] = HL_STRING;
		if (c == '\\' && (*i + 1 < row->rsize)) {
			row->hl[*i + 1] = HL_STRING;
			*i += 2;
			return (1);
		}
		if (c == *in_string) {
			*in_string = 0;
		}
		++*i;
		*prev_sep = 1;
		return (1);
	} else if (c == '"' || c == '\'') {
		*in_string = c;
		row->hl[*i] = HL_STRING;
		++*i;
		return (1);
	}
	return (0);
}

int
highlight_number(t_erow *row, int *i, int *prev_sep, unsigned char prev_hl)
{
	char	c = row->render[*i];

	if ((isdigit(c) && (*prev_sep || prev_hl == HL_NUMBER))
			|| (c == '.' && prev_hl == HL_NUMBER)) {
		row->hl[*i] = HL_NUMBER;
		++*i;
		*prev_sep = 0;
		return (1);
	}
	return (0);
}
