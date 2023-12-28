/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 14:37:35 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/28 19:27:44 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

int	is_page_keys(char *seq)
{
	if (seq[1] >= '0' && seq[1] <= '9')
	{
		if (read(STDIN_FILENO, &seq[2], 1) != 1)
			return ('\x1b');
		if (seq[2] == '~')
		{
			if (seq[1] == '5')
				return (PAGE_UP);
			else if (seq[1] == '6')
				return (PAGE_DOWN);
		}
	}
	return (0);
}

int	is_arrow_keys(char *seq)
{
	if (seq[1] == 'A')
		return (ARROW_UP);
	else if (seq[1] == 'B')
		return (ARROW_DOWN);
	else if (seq[1] == 'C')
		return (ARROW_RIGHT);
	else if (seq[1] == 'D')
		return (ARROW_LEFT);
	else
		return (0);
}

int	read_escape_sequences(void)
{
	int		key;
	char	seq[3];

	if (read(STDIN_FILENO, &seq[0], 1) != 1)
		return ('\x1b');
	if (read(STDIN_FILENO, &seq[1], 1) != 1)
		return ('\x1b');
	if (seq[0] == '[')
	{
		key = is_page_keys(seq);
		if (key)
			return (key);
		else
		{
			key = is_arrow_keys(seq);
			if (key)
				return (key);
		}
	}
	return ('\x1b');
}
