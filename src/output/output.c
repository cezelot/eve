/* ************************************************************************** */
/*                                                                            */
/*   output.c - standard output routines                                      */
/*                                                                            */
/*   Created: 2023/12/06 18:08:14 by cezelot                                  */
/*   Updated: 2024/07/23 19:50:43 by cezelot                                  */
/*                                                                            */
/*   Copyright (C) 2024 Ismael Benjara                                        */
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

#include "../eve.h"

/* Scroll the file if the cursor has moved outside of the visible window.  */
static void
scroll(t_env *env)
{
	env->rx = 0;
	if (env->cy < env->numrows) {
		env->rx = row_cx_to_rx(&env->row[env->cy], env->cx);
	}
	if (env->cy < env->rowoff) {
		env->rowoff = env->cy;
	}
	if (env->cy >= env->rowoff + env->screenrows) {
		env->rowoff = env->cy - env->screenrows + 1;
	}
	if (env->rx < env->coloff) {
		env->coloff = env->rx;
	}
	if (env->rx >= env->coloff + env->screencols) {
		env->coloff = env->rx - env->screencols + 1;
	}
}

void
draw_message_bar(t_env *env, t_abuf *abuf)
{
	int	msglen;

	abuf_append(abuf, "\x1b[K", 3);
	msglen = strlen(env->statusmsg);
	if (msglen > env->screencols) {
		msglen = env->screencols;
	}
	if (msglen && time(NULL) - env->statusmsg_time < 5) {
		abuf_append(abuf, env->statusmsg, msglen);
	}
}

static void
draw_status_bar(t_env *env, t_abuf *abuf)
{
	char	status[80];
	char	rstatus[80];
	int	len;
	int	rlen;

	len = snprintf(status, sizeof(status), "%.20s - %d lines %s",
		env->filename ? env->filename : "[No Name]", env->numrows,
		env->dirty ? "(modified)" : "");
	rlen = snprintf(rstatus, sizeof(rstatus), "%d,%d", env->cy + 1,
		env->cx + 1);
	abuf_append(abuf, "\x1b[7m", 4);
	if (len > env->screencols) {
		len = env->screencols;
	}
	abuf_append(abuf, status, len);
	while (len < env->screencols) {
		if (env->screencols - len == rlen) {
			abuf_append(abuf, rstatus, rlen);
			break ;
		} else {
			abuf_append(abuf, " ", 1);
			++len;
		}
	}
	abuf_append(abuf, "\x1b[m", 3);
	abuf_append(abuf, "\r\n", 2);
}

/* If the the program was run without a file, draw a column of tildes
   on the left hand side of the screen.  Otherwise, draw the text
   buffer and add a tilde at the beginning of the line that come after
   the end of the file.  */
static void
draw_rows(t_env *env, t_abuf *abuf)
{
	int	n = 0;
	int	filerow;

	while (n < env->screenrows) {
		filerow = n + env->rowoff;
		if (filerow >= env->numrows) {
			display_tilde(env, abuf, n);
		} else {
			display_text_buffer(env, abuf, filerow);
		}
		abuf_append(abuf, "\x1b[K", 3);
		abuf_append(abuf, "\r\n", 2);
		++n;
	}
}

void
refresh_screen(t_env *env)
{
	t_abuf	abuf;
	char	buf[32];

	abuf.buf = NULL;
	abuf.len = 0;
	scroll(env);
	abuf_append(&abuf, "\x1b[?25l", 6);
	abuf_append(&abuf, "\x1b[H", 3);
	draw_rows(env, &abuf);
	draw_status_bar(env, &abuf);
	draw_message_bar(env, &abuf);
	snprintf(buf, sizeof(buf), "\x1b[%d;%dH",
		(env->cy - env->rowoff) + 1, (env->rx - env->coloff) + 1);
	abuf_append(&abuf, buf, strlen(buf));
	abuf_append(&abuf, "\x1b[?25h", 6);
	write(STDOUT_FILENO, abuf.buf, abuf.len);
	abuf_free(&abuf);
}
