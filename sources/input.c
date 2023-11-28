/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:32:33 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/28 21:02:18 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	editor_process_keypress(void)
{
	char	c;

	c = editor_read_key();
	if (c == ('q' & 0x1f))
		exit(0);
}
