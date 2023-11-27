/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:32:33 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/27 18:34:37 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

void	editor_process_keypress(void)
{
	char	c;

	c = editor_read_key();
	if (c == CTRL_KEY('q'))
		exit(0);
}
