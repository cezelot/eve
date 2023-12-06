/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eve.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:17:10 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/06 18:24:37 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVE_H
# define EVE_H

# include <ctype.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

int		read_key(int *pi, char *pc);
char	editor_read_key(void);
void	editor_refresh_screen(void);
void	die(const char *str);
void	disable_raw_mode(void);
void	enable_raw_mode(void);
void	editor_process_keypress(void);

#endif
