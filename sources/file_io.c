/* ************************************************************************** */
/*                                                                            */
/*   file_io.c                                                      .a888b    */
/*   by: cezelot <cezelot@proton.me>                               d8P'88P    */
/*                                                                d8P         */
/*   Created: 2023/12/29 16:01:01 by cezelot                     d8P.a8P      */
/*   Updated: 2024/06/23 21:29:50 by cezelot                     d888P'       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

static int	has_newline_or_carriage_return(char *line, ssize_t linelen)
{
	return (line[linelen - 1] == '\n' || line[linelen - 1] == '\r');
}

void	editor_open(t_env *env, char *filename)
{
	FILE	*fp;
	char	*line;
	size_t	linecap;
	ssize_t	linelen;

	free(env->filename);
	env->filename = strdup(filename);
	fp = fopen(filename, "r");
	if (!fp)
	{
		free(env->filename);
		die(__FILE__, __LINE__, "cannot open the file");
	}
	line = NULL;
	linecap = 0;
	while (1)
	{
		linelen = getline(&line, &linecap, fp);
		if (linelen == -1)
			break ;
		while (linelen > 0 && has_newline_or_carriage_return(line, linelen))
			--linelen;
		editor_append_row(env, line, linelen);
	}
	free(line);
	fclose(fp);
}
