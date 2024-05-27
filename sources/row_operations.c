/* ************************************************************************** */
/*                                                                            */
/*   row_operations.c                                               .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/31 18:08:27 by cezelot                     d8P.a8P      */
/*   Updated: 2023/12/31 19:11:30 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	editor_append_row(t_env *env, char *str, size_t len)
{
	int	at;

	env->row = realloc(env->row, sizeof(t_erow) * (env->numrows + 1));
	at = env->numrows;
	env->row[at].size = len;
	env->row[at].chars = malloc(len + 1);
	memcpy(env->row[at].chars, str, len);
	env->row[at].chars[len] = '\0';
	env->numrows++;
}
