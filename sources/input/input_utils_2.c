/* ************************************************************************** */
/*                                                                            */
/*   input_utils_2.c                                                .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2024/05/30 17:10:05 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/30 21:00:32 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/eve.h"

void	change_page(t_env *env, int c)
{
	int	times;

	times = env->screenrows;
	while (times--)
	{
		if (c == PAGE_UP)
			editor_move_cursor(env, ARROW_UP);
		else
			editor_move_cursor(env, ARROW_DOWN);
	}
}

void	move_cursor_to_end_line(t_env *env)
{
	if (env->cy < env->numrows)
		env->cx = env->row[env->cy].size;
}