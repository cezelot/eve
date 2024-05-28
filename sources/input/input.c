/* ************************************************************************** */
/*                                                                            */
/*   input.c                                                        .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/11/27 18:32:33 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/28 16:45:46 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

static void	editor_move_cursor(t_env *env, int key)
{
	t_erow	*row;
	int		rowlen;

	rowlen = 0;
	if (env->cy >= env->numrows)
		row = NULL;
	else
		row = &env->row[env->cy];
	if (key == ARROW_LEFT)
		move_cursor_left(env);
	if (key == ARROW_RIGHT)
		move_cursor_right(env, row);
	if (key == ARROW_UP)
		move_cursor_up(env);
	if (key == ARROW_DOWN)
		move_cursor_down(env);
	snap_cursor_to_end_of_line(env, row, rowlen);
}

static void	process_page_keys(t_env *env, int c)
{
	int	times;

	times = env->screenrows;
	if (c == PAGE_UP)
		env->cy = env->rowoff;
	else if (c == PAGE_DOWN)
	{
		env->cy = env->rowoff + env->screenrows - 1;
		if (env->cy > env->numrows)
			env->cy = env->numrows;
	}
	while (times--)
	{
		if (c == PAGE_UP)
			editor_move_cursor(env, ARROW_UP);
		else
			editor_move_cursor(env, ARROW_DOWN);
	}
}

static void	process_esc_seq_keys(int c, t_env *env)
{
	if (c == HOME_KEY)
		env->cx = 0;
	else if (c == END_KEY)
	{
		if (env->cy < env->numrows)
			env->cx = env->row[env->cy].size;
	}
	else if ((c == PAGE_UP) || (c == PAGE_DOWN))
		process_page_keys(env, c);
	else if ((c == ARROW_LEFT) || (c == ARROW_RIGHT) \
			|| (c == ARROW_UP) || (c == ARROW_DOWN))
		editor_move_cursor(env, c);
}

void	editor_process_keypress(t_env *env)
{
	int	c;

	c = editor_read_key();
	if (c == ('q' & 0x1f))
	{
		write(STDOUT_FILENO, "\x1b[2J", 4);
		write(STDOUT_FILENO, "\x1b[H", 3);
		exit(0);
	}
	else
		process_esc_seq_keys(c, env);
}
