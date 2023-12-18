/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 18:08:14 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/18 19:08:01 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	abuf_append(t_abuf *abuf, const char *str, int len);
void	abuf_free(t_abuf *abuf);

void	editor_draw_rows(t_abuf *abuf, t_env *env)
{
	int	n;

	n = 0;
	while (n < env->screenrows)
	{
		abuf_append(abuf, "~", 1);
		if (n++ < env->screenrows - 1)
			abuf_append(abuf, "\r\n", 2);
	}
}

void	editor_refresh_screen(t_env *env)
{
	t_abuf	abuf;

	abuf.buf = NULL;
	abuf.len = 0;
	abuf_append(&abuf, "\x1b[2J", 4);
	abuf_append(&abuf, "\x1b[H", 3);
	editor_draw_rows(&abuf, env);
	abuf_append(&abuf, "\x1b[H", 3);
	write(STDOUT_FILENO, abuf.buf, abuf.len);
	abuf_free(&abuf);
}
