/* ************************************************************************** */
/*                                                                            */
/*   main.c                                                         .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/11/26 12:20:29 by cezelot                     d8P.a8P      */
/*   Updated: 2024/06/23 21:24:11 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

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
		die(__FILE__, __LINE__, "failed to get terminal size");
	env->screenrows -= 2;
}

int	main(int ac, char **av)
{
	t_env	env;

	enable_raw_mode();
	init_editor(&env);
	if (ac >= 2)
		editor_open(&env, av[1]);
	editor_set_status_message(&env, "Help: Ctrl-Q = quit");
	while (1)
	{
		editor_refresh_screen(&env);
		editor_process_keypress(&env);
	}
	return (0);
}
