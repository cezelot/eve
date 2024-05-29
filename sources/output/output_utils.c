/* ************************************************************************** */
/*                                                                            */
/*   output_utils.c                                                 .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2024/05/29 10:19:15 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/29 11:34:07 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

void	display_text_buffer(t_env *env, t_abuf *abuf, int filerow)
{
	int	len;

	len = env->row[filerow].rsize - env->coloff;
	if (len < 0)
		len = 0;
	if (len > env->screencols)
		len = env->screencols;
	abuf_append(abuf, &env->row[filerow].render[env->coloff], len);
}

void	display_welcome_message(t_env *env, t_abuf *abuf)
{
	char	welcome[80];
	int		welcomelen;
	int		padding;

	welcomelen = snprintf(welcome, sizeof(welcome), \
		"eve editor -- version %s", EVE_VERSION);
	if (welcomelen > env->screencols)
		welcomelen = env->screencols;
	padding = (env->screencols - welcomelen) / 2;
	if (padding)
	{
		abuf_append(abuf, "~", 1);
		--padding;
	}
	while (padding--)
		abuf_append(abuf, " ", 1);
	abuf_append(abuf, welcome, welcomelen);
}
