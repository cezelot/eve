/* ************************************************************************** */
/*                                                                            */
/*   output_2.c                                                               */
/*                                                                            */
/*   Created: 2024/05/29 10:19:15 by cezelot                                  */
/*   Updated: 2024/09/05 10:25:30 by cezelot                                  */
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

void
set_status_message(t_env *env, const char *format, ...)
{
	va_list	ap;

	va_start(ap, format);
	vsnprintf(env->statusmsg, sizeof(env->statusmsg), format, ap);
	va_end(ap);
	env->statusmsg_time = time(NULL);
}

static void
print_color_escape_sequence(t_abuf *abuf, int color)
{
	char buf[16];
	int clen;

	clen = snprintf(buf, sizeof(buf), "\x1b[%dm", color);
	abuf_append(abuf, buf, clen);
}

void
display_text_buffer(t_env *env, t_abuf *abuf, int filerow)
{
	unsigned char	*hl;
	char		*s;
	int		len;
	int		color = 0;
	int		current_color = -1;

	hl = &env->row[filerow].hl[env->coloff];
	s = &env->row[filerow].render[env->coloff];
	len = env->row[filerow].rsize - env->coloff;
	if (len < 0) {
		len = 0;
	}
	if (len > env->screencols) {
		len = env->screencols;
	}
	for (int i = 0; i < len; ++i) {
		if (hl[i] == HL_NORMAL) {
			if (current_color != -1) {
				abuf_append(abuf, "\x1b[39m", 5);
				current_color = -1;
			}
			abuf_append(abuf, &s[i], 1);
		} else {
			color = syntax_to_color(hl[i]);
			if (color != current_color) {
				current_color = color;
				print_color_escape_sequence(abuf, current_color);
			}
			abuf_append(abuf, &s[i], 1);
		}
	}
	abuf_append(abuf, "\x1b[39m", 5);
}

void
display_welcome_message(t_env *env, t_abuf *abuf)
{
	char	welcome[80];
	int	welcomelen;
	int	padding;

	welcomelen = snprintf(welcome, sizeof(welcome),
		"eve - version %s", VERSION);
	if (welcomelen > env->screencols) {
		welcomelen = env->screencols;
	}
	padding = (env->screencols - welcomelen) / 2;
	if (padding) {
		abuf_append(abuf, "~", 1);
		--padding;
	}
	while (padding--) {
		abuf_append(abuf, " ", 1);
	}
	abuf_append(abuf, welcome, welcomelen);
}

void
display_tilde(t_env *env, t_abuf *abuf, int n)
{
	if (env->numrows == 0 && n == env->screenrows / 3) {
		if (n == env->screenrows / 3) {
			display_welcome_message(env, abuf);
		}
	} else {
		abuf_append(abuf, "~", 1);
	}
}
