/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:20:29 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/31 20:48:03 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	init_editor(t_env *env)
{
	env->cx = 0;
	env->cy = 0;
	env->rowoff = 0;
	env->numrows = 0;
	env->row = NULL;
	if (get_window_size(&env->screenrows, \
	&env->screencols) == -1)
		die("get_window_size screensize");
}

int	main(int ac, char **av)
{
	t_env	env;

	enable_raw_mode();
	init_editor(&env);
	if (ac >= 2)
		editor_open(&env, av[1]);
	atexit(disable_raw_mode);
	while (1)
	{
		editor_refresh_screen(&env);
		editor_process_keypress(&env);
	}
	return (0);
}
