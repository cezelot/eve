/* ************************************************************************** */
/*                                                                            */
/*   terminal_3.c                                                   .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/28 14:37:35 by cezelot                     d8P.a8P      */
/*   Updated: 2023/12/29 15:25:53 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

int	is_home_or_end_keys(char *seq)
{
	if (seq[1] == 'H')
		return (HOME_KEY);
	else if (seq[1] == 'F')
		return (END_KEY);
	else
		return (0);
}

int	is_seq_keys_2(char *seq)
{
	if (seq[1] >= '0' && seq[1] <= '9')
	{
		if (read(STDIN_FILENO, &seq[2], 1) != 1)
			return ('\x1b');
		if (seq[2] == '~')
		{
			if (seq[1] == '1')
				return (HOME_KEY);
			else if (seq[1] == '3')
				return (DEL_KEY);
			else if (seq[1] == '4')
				return (END_KEY);
			else if (seq[1] == '5')
				return (PAGE_UP);
			else if (seq[1] == '6')
				return (PAGE_DOWN);
			else if (seq[1] == '7')
				return (HOME_KEY);
			else if (seq[1] == '8')
				return (END_KEY);
		}
	}
	return (0);
}

int	is_seq_keys(char *seq)
{
	if (seq[1] == 'A')
		return (ARROW_UP);
	else if (seq[1] == 'B')
		return (ARROW_DOWN);
	else if (seq[1] == 'C')
		return (ARROW_RIGHT);
	else if (seq[1] == 'D')
		return (ARROW_LEFT);
	else if (seq[1] == 'H')
		return (HOME_KEY);
	else if (seq[1] == 'F')
		return (END_KEY);
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
		key = is_seq_keys_2(seq);
		if (key)
			return (key);
		else
		{
			key = is_seq_keys(seq);
			if (key)
				return (key);
		}
	}
	else if (seq[0] == 'O')
		return (is_home_or_end_keys(seq));
	return ('\x1b');
}
