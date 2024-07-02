/* ************************************************************************** */
/*                                                                            */
/*   main.c                        eve - simple terminal-based text editor.   */
/*                                                                            */
/*   Created: 2023/11/26 12:20:29 by cezelot                                  */
/*   Updated: 2024/07/02 12:23:30 by cezelot                                  */
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

void	die(const char *format, ...)
{
	va_list	ap;

	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	exit(1);
}

void	close_editor(t_env *env)
{
	int	i;

	i = 0;
	free(env->filename);
	while (i < env->numrows)
	{
		free(env->row[i].chars);
		free(env->row[i++].render);
	}
	free(env->row);
}

static void	init_editor(t_env *env)
{
	env->cx = 0;
	env->cy = 0;
	env->rx = 0;
	env->rowoff = 0;
	env->coloff = 0;
	env->numrows = 0;
	env->row = NULL;
	env->filename = NULL;
	env->statusmsg[0] = '\0';
	env->statusmsg_time = 0;
	if (get_window_size(&env->screenrows, \
	&env->screencols) == -1)
		die("%s:%d: unable to get terminal size: %s", \
			__FILE__, __LINE__, strerror(errno));
	env->screenrows -= 2;
}

int	main(int ac, char **av)
{
	t_env	env;
	int		option_index;

	option_index = 0;
	parse_options(ac, av, &option_index);
	enable_raw_mode();
	init_editor(&env);
	if (option_index < ac)
		editor_open(&env, av[option_index]);
	editor_set_status_message(&env, "Help: Ctrl-Q = quit");
	while (1)
	{
		editor_refresh_screen(&env);
		editor_process_keypress(&env);
	}
	return (0);
}
