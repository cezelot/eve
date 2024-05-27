/* ************************************************************************** */
/*                                                                            */
/*   output.c                                                       .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/06 18:08:14 by cezelot                     d8P.a8P      */
/*   Updated: 2024/01/01 19:19:27 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	editor_scroll(t_env *env)
{
	if (env->cy < env->rowoff)
		env->rowoff = env->cy;
	if (env->cy >= env->rowoff + env->screenrows)
		env->rowoff = env->cy - env->screenrows + 1;
}

void	display_text_buffer(t_abuf *abuf, t_env *env, int filerow)
{
	int	len;

	len = env->row[filerow].size;
	if (len > env->screencols)
		len = env->screencols;
	abuf_append(abuf, env->row[filerow].chars, len);
}

void	display_welcome_message(t_abuf *abuf, t_env *env)
{
	char	welcome[80];
	int		welcomelen;
	int		padding;

	welcomelen = snprintf(welcome, sizeof(welcome), \
		"eve editor -- version %s", EVE_VERSION);
	if (welcomelen > env->screencols)
		welcomelen = env->screencols;
	padding = (env->screencols - welcomelen) / 2;
	if (padding)
	{
		abuf_append(abuf, "~", 1);
		padding--;
	}
	while (padding--)
		abuf_append(abuf, " ", 1);
	abuf_append(abuf, welcome, welcomelen);
}

void	editor_draw_rows(t_abuf *abuf, t_env *env)
{
	int	n;
	int	filerow;

	n = 0;
	while (n < env->screenrows)
	{
		filerow = n + env->rowoff;
		if (filerow >= env->numrows)
		{
			if (env->numrows == 0 && n == env->screenrows / 3)
			{
				if (n == env->screenrows / 3)
					display_welcome_message(abuf, env);
			}
			else
				abuf_append(abuf, "~", 1);
		}
		else
			display_text_buffer(abuf, env, filerow);
		abuf_append(abuf, "\x1b[K", 3);
		if (n++ < env->screenrows - 1)
			abuf_append(abuf, "\r\n", 2);
	}
}

void	editor_refresh_screen(t_env *env)
{
	t_abuf	abuf;
	char	buf[32];

	abuf.buf = NULL;
	abuf.len = 0;
	editor_scroll(env);
	abuf_append(&abuf, "\x1b[?25l", 6);
	abuf_append(&abuf, "\x1b[H", 3);
	editor_draw_rows(&abuf, env);
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", \
		(env->cy - env->rowoff) + 1, env->cx + 1);
	abuf_append(&abuf, buf, strlen(buf));
	abuf_append(&abuf, "\x1b[?25h", 6);
	write(STDOUT_FILENO, abuf.buf, abuf.len);
	abuf_free(&abuf);
}
