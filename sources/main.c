/* ************************************************************************** */
/*                                                                            */
/*   main.c                                                         .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/11/26 12:20:29 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/28 15:34:32 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

static void	init_editor(t_env *env)
{
	env->cx = 0;
	env->cy = 0;
	env->rx = 0;
	env->rowoff = 0;
	env->coloff = 0;
	env->numrows = 0;
	env->row = NULL;
	if (get_window_size(&env->screenrows, \
	&env->screencols) == -1)
		die("get_window_size screensize");
}

int	main(int ac, char **av)
{
	t_env	env;

	atexit(disable_raw_mode);
	enable_raw_mode();
	init_editor(&env);
	if (ac >= 2)
		editor_open(&env, av[1]);
	while (1)
	{
		editor_refresh_screen(&env);
		editor_process_keypress(&env);
	}
	return (0);
}
