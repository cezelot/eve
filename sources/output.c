/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:08:14 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/29 16:20:59 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	abuf_append(t_abuf *abuf, const char *str, int len);
void	abuf_free(t_abuf *abuf);

void	draw_welcome_message(t_abuf *abuf, t_env *env)
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
	int	len;

	n = 0;
	while (n < env->screenrows)
	{
		if (n >= env->numrows)
		{
			if (n == env->screenrows / 3)
				draw_welcome_message(abuf, env);
			else
				abuf_append(abuf, "~", 1);
		}
		else
		{
			len = env->row.size;
			if (len > env->screencols)
				len = env->screencols;
			abuf_append(abuf, env->row.chars, len);
		}
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
	abuf_append(&abuf, "\x1b[?25l", 6);
	abuf_append(&abuf, "\x1b[H", 3);
	editor_draw_rows(&abuf, env);
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH", env->cy + 1, env->cx + 1);
	abuf_append(&abuf, buf, strlen(buf));
	abuf_append(&abuf, "\x1b[?25h", 6);
	write(STDOUT_FILENO, abuf.buf, abuf.len);
	abuf_free(&abuf);
}
