/* ************************************************************************** */
/*                                                                            */
/*   syntax_highlighting_2.c                                                  */
/*                                                                            */
/*   Created: 2024/09/07 21:39:22 by cezelot                                  */
/*   Updated: 2024/09/07 21:41:57 by cezelot                                  */
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
is_separator(int c)
{
	return (isspace(c) || c == '\0'
		|| strchr(",.()+-/*=~%<>[];", c) != NULL);
}

static void
rehighlight_buffer(t_env *env)
{
	int	filerow = 0;

	while (filerow < env->numrows) {
		update_syntax(env, &env->row[filerow++]);
	}
}

int
match_extension(t_env *env, char *ext, t_syntax *syntax)
{
	size_t	i = 0;
	int	is_ext = 0;

	while (syntax->filematch[i]) {
		is_ext = (syntax->filematch[i][0] == '.');
		if ((is_ext && ext && !strcmp(ext, syntax->filematch[i]))
				|| (!is_ext && strstr(env->filename,
					syntax->filematch[i]))) {
			env->syntax = syntax;
			rehighlight_buffer(env);
			return (1);
		}
		++i;
	}
	return (0);

}
