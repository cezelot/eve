/* ************************************************************************** */
/*                                                                            */
/*   input.c                                                        .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/11/27 18:32:33 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/31 10:56:01 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

void	editor_move_cursor(t_env *env, int key)
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
	snap_cursor_to_end_line(env, row, rowlen);
}

static void	process_page_keys(t_env *env, int c)
{
	if (c == PAGE_UP)
		env->cy = env->rowoff;
	else
	{
		env->cy = env->rowoff + env->screenrows - 1;
		if (env->cy > env->numrows)
			env->cy = env->numrows;
	}
	change_page(env, c);
}

static void	process_esc_seq_keys(int c, t_env *env)
{
	if (c == HOME_KEY)
		env->cx = 0;
	else if (c == END_KEY)
		move_cursor_to_end_line(env);
	else if (is_page_keys(c))
		process_page_keys(env, c);
	else if (is_arrow_keys(c))
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
		close_editor(env);
		exit(0);
	}
	else
		process_esc_seq_keys(c, env);
}
