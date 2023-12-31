/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   row_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 18:08:27 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/31 19:11:30 by bhamed           ###   ########.fr       */
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
