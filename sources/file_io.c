/* ************************************************************************** */
/*                                                                            */
/*   file_io.c                                                      .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/29 16:01:01 by cezelot                     d8P.a8P      */
/*   Updated: 2024/03/15 09:19:42 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

void	editor_open(t_env *env, char *filename)
{
	FILE	*fp;
	char	*line;
	size_t	linecap;
	ssize_t	linelen;

	fp = fopen(filename, "r");
	if (!fp)
		die("fopen");
	line = NULL;
	linecap = 0;
	while (1)
	{
		linelen = getline(&line, &linecap, fp);
		if (linelen == -1)
			break ;
		while (linelen > 0 && (line[linelen - 1] == '\n' || \
								line[linelen - 1] == '\r'))
			--linelen;
		editor_append_row(env, line, linelen);
	}
	free(line);
	fclose(fp);
}
