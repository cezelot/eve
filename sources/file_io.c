/* ************************************************************************** */
/*                                                                            */
/*   file_io.c                                                                */
/*                                                                            */
/*   Created: 2023/12/29 16:01:01 by cezelot                                  */
/*   Updated: 2024/07/02 12:25:10 by cezelot                                  */
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

static int	has_newline_or_carriage_return(char *line, ssize_t linelen)
{
	return (line[linelen - 1] == '\n' || line[linelen - 1] == '\r');
}

void	editor_open(t_env *env, char *filename)
{
	FILE	*fp;
	char	*line;
	size_t	linecap;
	ssize_t	linelen;

	free(env->filename);
	env->filename = strdup(filename);
	fp = fopen(filename, "r");
	if (!fp)
	{
		free(env->filename);
		die("%s:%d: unable to open file %s: %s", \
			__FILE__, __LINE__, filename, strerror(errno));
	}
	line = NULL;
	linecap = 0;
	while (1)
	{
		linelen = getline(&line, &linecap, fp);
		if (linelen == -1)
			break ;
		while (linelen > 0 && has_newline_or_carriage_return(line, linelen))
			--linelen;
		editor_append_row(env, line, linelen);
	}
	free(line);
	fclose(fp);
}
