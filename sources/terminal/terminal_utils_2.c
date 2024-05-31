/* ************************************************************************** */
/*                                                                            */
/*   terminal_utils_2.c                                             .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2024/05/31 12:49:14 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/31 13:35:27 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

int	get_nav_key(char *seq)
{
	if (seq[1] == '1' || seq[1] == '7')
		return (HOME_KEY);
	else if (seq[1] == '3')
		return (DEL_KEY);
	else if (seq[1] == '4' || seq[1] == '8')
		return (END_KEY);
	else if (seq[1] == '5')
		return (PAGE_UP);
	else if (seq[1] == '6')
		return (PAGE_DOWN);
	return (0);
}
