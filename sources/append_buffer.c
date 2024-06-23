/* ************************************************************************** */
/*                                                                            */
/*   append_buffer.c                                                .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/18 14:16:44 by cezelot                     d8P.a8P      */
/*   Updated: 2024/06/20 11:02:16 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	abuf_append(t_abuf *abuf, const char *str, int len)
{
	char	*new_buf;

	new_buf = realloc(abuf->buf, abuf->len + len);
	if (new_buf == NULL)
		return ;
	memcpy(&new_buf[abuf->len], str, len);
	abuf->buf = new_buf;
	abuf->len += len;
}

void	abuf_free(t_abuf *abuf)
{
	free(abuf->buf);
}
