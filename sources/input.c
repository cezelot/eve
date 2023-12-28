/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:32:33 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/25 16:07:51 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	editor_move_cursor(t_env *env, char key)
{
	if (key == 'h')
		env->cx--;
	else if (key == 'l')
		env->cx++;
	else if (key == 'k')
		env->cy--;
	else if (key == 'j')
		env->cy++;
}

void	editor_process_keypress(t_env *env)
{
	char	c;

	c = editor_read_key();
	if (c == ('q' & 0x1f))
	{
		write(STDOUT_FILENO, "\x1b[2J", 4);
		write(STDOUT_FILENO, "\x1b[H", 3);
		exit(0);
	}
	else if ((c == 'k') || (c == 'h') || (c == 'j') || (c == 'l'))
		editor_move_cursor(env, c);
}
