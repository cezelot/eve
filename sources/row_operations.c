/* ************************************************************************** */
/*                                                                            */
/*   row_operations.c                                               .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/31 18:08:27 by cezelot                     d8P.a8P      */
/*   Updated: 2024/05/28 15:53:04 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

int	editor_row_cx_to_rx(t_erow *row, int cx)
{
	int	rx;
	int	i;

	rx = 0;
	i = 0;
	while (i < cx)
	{
		if (row->chars[i++] == '\t')
			rx += (EVE_TAB_STOP - 1) - (rx % EVE_TAB_STOP);
		++rx;
	}
	return (rx);
}

static void	render_tab(char *render, int *index)
{
	render[(*index)++] = ' ';
	while (*index % EVE_TAB_STOP)
		render[(*index)++] = ' ';
}

static void	editor_update_row(t_erow *row)
{
	int	i;
	int	n;
	int	tabs;

	i = 0;
	n = 0;
	tabs = 0;
	while (n < row->size)
		if (row->chars[n++] == '\t')
			++tabs;
	free(row->render);
	row->render = malloc(row->size + tabs * (EVE_TAB_STOP - 1) + 1);
	n = 0;
	while (n < row->size)
	{
		if (row->chars[n] == '\t')
			render_tab(row->render, &i);
		else
			row->render[i++] = row->chars[n];
		++n;
	}
	row->render[i] = '\0';
	row->rsize = i;
}

void	editor_append_row(t_env *env, char *str, size_t len)
{
	size_t	at;

	env->row = realloc(env->row, sizeof(t_erow) * (env->numrows + 1));
	at = env->numrows;
	env->row[at].size = len;
	env->row[at].chars = malloc(len + 1);
	memcpy(env->row[at].chars, str, len);
	env->row[at].chars[len] = '\0';
	env->row[at].rsize = 0;
	env->row[at].render = NULL;
	editor_update_row(&env->row[at]);
	env->numrows++;
}
