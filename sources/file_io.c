/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:01:01 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/29 17:09:32 by bhamed           ###   ########.fr       */
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
	linelen = getline(&line, &linecap, fp);
	if (linelen != -1)
	{
		while (linelen > 0 && (line[linelen - 1] == '\n' || \
								line[linelen - 1] == '\r'))
			linelen--;
		env->row.size = linelen;
		env->row.chars = malloc(linelen + 1);
		memcpy(env->row.chars, line, linelen);
		env->row.chars[linelen] = '\0';
		env->numrows = 1;
	}
	free(line);
	fclose(fp);
}
