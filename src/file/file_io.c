/* ************************************************************************** */
/*                                                                            */
/*   file_io.c - file input/output routines                                   */
/*                                                                            */
/*   Created: 2023/12/29 16:01:01 by cezelot                                  */
/*   Updated: 2024/08/16 17:00:27 by alberrod                                 */
/*                                                                            */
/*   Copyright (C) 2024 Ismael B. Hamed, Alberto Rodriguez                    */
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

/* Convert ROW structs into a single string.
   Its length will be assigned to BUFLEN.
   Return the string.  */
static char *
rows_to_string(t_env *env, int *buflen)
{
	char	*buf;
	char	*p;
	int	len = 0;
	int	i = 0;

	while (i < env->numrows) {
		len += env->row[i++].size + 1;
	}
	*buflen = len;
	buf = malloc(len * sizeof(*buf));
	if (buf == NULL) {
		die("%s:%d: %s", __FILE__, __LINE__, strerror(errno));
	}
	p = buf;
	i = 0;
	while (i < env->numrows) {
		memcpy(p, env->row[i].chars, env->row[i].size);
		p += env->row[i++].size;
		*p++ = '\n';
	}
	return (buf);
}

/* Write the current text buffer to disk.  */
void
save(t_env *env)
{
	char	*buf;
	int	len = 0;
	int	fd;

	if (env->filename == NULL && set_filename(env) == -1) {
		return ;
	}
	buf = rows_to_string(env, &len);
	fd = open_save_file(env, buf);
	if (fd == -1) {
		return ;
	}
	if (truncate_file(fd, len, buf, env) == -1) {
		return ;
	}
	if (write_file(fd, len, buf, env) == -1) {
		return ;
	}
	set_status_message(env, "%d bytes written", len);
	cleanup(fd, buf);
	env->dirty = 0;
}

/* Return true if LINE has a newline or a carriage return,
   otherwise return false.  */
static int
has_newline_or_carriage_return(char *line, ssize_t linelen)
{
	return (line[linelen - 1] == '\n' || line[linelen - 1] == '\r');
}

/* Open and read FILENAME.  */
void
open_file(t_env *env, char *filename)
{
	FILE	*fp;
	char	*line;
	size_t	linecap;
	ssize_t	linelen;

	free(env->filename);
	env->filename = strdup(filename);
	fp = fopen(filename, "r");
	if (!fp) {
		free(env->filename);
		die("%s:%d: unable to open file %s: %s",
			__FILE__, __LINE__, filename, strerror(errno));
	}
	line = NULL;
	linecap = 0;
	while (1) {
		linelen = getline(&line, &linecap, fp);
		if (linelen == -1) {
			break ;
		}
		while (linelen > 0
				&& has_newline_or_carriage_return(line,
					linelen)) {
			--linelen;
		}
		insert_row(env, line, linelen, env->numrows);
	}
	free(line);
	fclose(fp);
	env->dirty = 0;
}
