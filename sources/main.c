/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:20:29 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/10 23:58:22 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	die(const char *str)
{
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	perror(str);
	exit(1);
}

void	init_editor(t_env *env)
{
	if (get_window_size(&env->screenrows, \
	&env->screencols) == -1)
		die("get_window_size screensize");
}

int	main(void)
{
	t_env	env;

	enable_raw_mode();
	init_editor(&env);
	atexit(disable_raw_mode);
	while (1)
	{
		editor_refresh_screen(&env);
		editor_process_keypress();
	}
	return (0);
}
