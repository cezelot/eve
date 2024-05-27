/* ************************************************************************** */
/*                                                                            */
/*   append_buffer.c                                                .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/18 14:16:44 by cezelot                     d8P.a8P      */
/*   Updated: 2023/12/25 15:28:48 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	abuf_append(t_abuf *abuf, const char *str, int len)
{
	char	*new;

	new = realloc(abuf->buf, abuf->len + len);
	if (new == NULL)
		return ;
	memcpy(&new[abuf->len], str, len);
	abuf->buf = new;
	abuf->len += len;
}

void	abuf_free(t_abuf *abuf)
{
	free(abuf->buf);
}
