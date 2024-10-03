/* ************************************************************************** */
/*                                                                            */
/*   syntax_highlighting.c                                                    */
/*                                                                            */
/*   Created: 2024/09/01 15:58:19 by cezelot                                  */
/*   Updated: 2024/10/03 19:16:39 by cezelot                                  */
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

/* Highlight the characters of ROW.  */
void
update_syntax(t_env *env, t_erow *row)
{
	char		*scs;
	unsigned char	prev_hl;
	int		prev_sep = 1;
	int		in_string = 0;
	int		scs_len;
	int		i = 0;

	row->hl = realloc(row->hl, row->rsize);
	if (row->hl == NULL) {
		return ;
	}
	memset(row->hl, HL_NORMAL, row->rsize);
	if (env->syntax == NULL) {
		return ;
	}
	scs = env->syntax->singleline_comment_start;
	if (scs) {
		scs_len = strlen(scs);
	} else {
		scs_len = 0;
	}
	while (i < row->rsize) {
		if (i > 0) {
			prev_hl = row->hl[i - 1];
		} else {
			prev_hl = HL_NORMAL;
		}
		if (scs_len && !in_string) {
			if (!strncmp(&row->render[i], scs, scs_len)) {
				memset(&row->hl[i], HL_COMMENT, row->rsize - i);
				break ;
			}
		}
		if (env->syntax->flags & HL_HIGHLIGHT_STRINGS) {
			if (highlight_string(row, &i, &prev_sep, &in_string)) {
				continue ;
			}
		}
		if (env->syntax->flags & HL_HIGHLIGHT_NUMBERS) {
			if (highlight_number(row, &i, &prev_sep, prev_hl)) {
				continue ;
			}
		}
		if (prev_sep) {
			if (highlight_keyword(row, env->syntax->keywords, &i,
					&prev_sep)) {
				continue ;
			}
		}
		prev_sep = is_separator(row->render[i]);
		++i;
	}
}

void
select_syntax_highlight(t_env *env)
{
	static char	*c_extensions[] = {
		".c",
		".h",
		".cpp",
		NULL
	};
	static char	*c_keywords[] = {
		"char", "short", "int", "long", "double", "float", "signed",
		"unsigned", "void", "const", "static", "extern", "if", "else",
		"while", "for", "switch", "case", "break", "continue", "return",

		"struct|", "union|", "typedef|", "enum|", "class|", NULL
	};
	static t_syntax	hldb[] = {
		{
			"c",
			c_extensions,
			c_keywords,
			"//",
			HL_HIGHLIGHT_NUMBERS | HL_HIGHLIGHT_STRINGS
		}
	};
	t_syntax	*syntax = NULL;
	char		*ext;
	size_t		i = 0;

	env->syntax = NULL;
	ext = strrchr(env->filename, '.');
	while (i < (sizeof(hldb) / sizeof(hldb[0]))) {
		syntax = &hldb[i++];
		if (match_extension(env, ext, syntax)) {
			return ;
		}
	}
}

/* Map values in hl to ANSI color codes.  */
int
syntax_to_color(int hl)
{
	switch (hl) {
	case HL_COMMENT:
		/* foreground dark gray */
		return (37);
	case HL_MATCH:
	case HL_KEYWORD1:
		/* foreground light blue */
		return (94);
	case HL_KEYWORD2:
		/* foreground green */
		return (32);
	case HL_STRING:
		/* foreground cyan */
		return (36);
	case HL_NUMBER:
		/* foreground light red */
		return (91);
	default:
		/* default foreground color */
		return (39);
	}
}
