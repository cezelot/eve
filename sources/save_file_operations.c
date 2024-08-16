/* ************************************************************************** */
/*                                                                            */
/*   save_file_operations.c - file saving-related helper operations           */
/*                                                                            */
/*   Created: 2024/08/16 17:00:27 by alberrod                                 */
/*   Updated: 2024/08/16 17:00:27 by alberrod                                 */
/*                                                                            */
/*   Copyright (C) 2024 Alberto Rodriguez                                     */
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

void	cleanup(int fd, char *buf)
{
	if (fd != -1) close(fd);
	if (buf != NULL)
	{
		free(buf);
		buf = NULL;
	}
}

int	set_filename(t_env *env)
{
	env->filename = prompt(env, "Save as: %s", NULL);
	if (env->filename == NULL)
	{
		set_status_message(env, "Save aborted");
		return -1;
	}
	return 0;
}

int	open_save_file(t_env *env, char *buf)
{
	int fd = open(env->filename, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
	{
		set_status_message(env, "Unable to save: %s", strerror(errno));
		cleanup(fd, buf);
	}
	return fd;
}

int	truncate_file(int fd, int len, char *buf, t_env *env)
{
	if (ftruncate(fd, len) == -1)
	{
		set_status_message(env, "Unable to truncate file: %s", strerror(errno));
		cleanup(fd, buf);
		return -1;
	}
	return 0;
}

int	write_file(int fd, int len, char *buf, t_env *env)
{
	if (write(fd, buf, len) != len)
	{
		set_status_message(env, "Unable to write file: %s", strerror(errno));
		cleanup(fd, buf);
		return -1;
	}
	return 0;
}
