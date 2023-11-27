/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:20:29 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/27 18:35:50 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/header.h"

int	main(void)
{
	enable_raw_mode();
	atexit(disable_raw_mode);
	while (1)
		editor_process_keypress();
	return (0);
}
