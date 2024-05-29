/* ************************************************************************** */
/*                                                                            */
/*   output.c                                                       .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/06 18:08:14 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/29 12:06:53 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

static void	editor_scroll(t_env *env)
{
	env->rx = 0;
	if (env->cy < env->numrows)
		env->rx = editor_row_cx_to_rx(&env->row[env->cy], env->cx);
	if (env->cy < env->rowoff)
		env->rowoff = env->cy;
	if (env->cy >= env->rowoff + env->screenrows)
		env->rowoff = env->cy - env->screenrows + 1;
	if (env->rx < env->coloff)
		env->coloff = env->rx;
	if (env->rx >= env->coloff + env->screencols)
		env->coloff = env->rx - env->screencols + 1;
}

static void	editor_draw_status_bar(t_env *env, t_abuf *abuf)
{
	char	status[80];
	char	rstatus[80];
	int		len;
	int		rlen;

	if (env->filename)
		len = snprintf(status, sizeof(status), "%.20s - %d lines", \
		env->filename, env->numrows);
	else
		len = snprintf(status, sizeof(status), "%.20s - %d lines", \
		"[No Name]", env->numrows);
	rlen = snprintf(rstatus, sizeof(rstatus), "%d/%d", env->cy + 1, \
	env->numrows);
	abuf_append(abuf, "\x1b[7m", 4);
	if (len > env->screencols)
		len = env->screencols;
	abuf_append(abuf, status, len);
	while (len++ < env->screencols)
	{
		if (env->screencols - len == rlen)
		{
			abuf_append(abuf, rstatus, rlen);
			break ;
		}
		else
			abuf_append(abuf, " ", 1);
	}
	abuf_append(abuf, "\x1b[m", 3);
}

static void	editor_draw_rows(t_env *env, t_abuf *abuf)
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
					display_welcome_message(env, abuf);
			}
			else
				abuf_append(abuf, "~", 1);
		}
		else
			display_text_buffer(env, abuf, filerow);
		abuf_append(abuf, "\x1b[K", 3);
		abuf_append(abuf, "\r\n", 2);
		++n;
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
	editor_draw_rows(env, &abuf);
	editor_draw_status_bar(env, &abuf);
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", \
		(env->cy - env->rowoff) + 1, (env->rx - env->coloff) + 1);
	abuf_append(&abuf, buf, strlen(buf));
	abuf_append(&abuf, "\x1b[?25h", 6);
	write(STDOUT_FILENO, abuf.buf, abuf.len);
	abuf_free(&abuf);
}
