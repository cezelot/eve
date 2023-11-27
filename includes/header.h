/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:17:10 by bhamed            #+#    #+#             */
/*   Updated: 2023/11/27 18:41:33 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include <ctype.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# define CTRL_KEY(k) ((k) & 0x1f)

void	die(const char *str);
void	disable_raw_mode(void);
void	enable_raw_mode(void);
char	editor_read_key(void);
void	editor_process_keypress(void);

#endif
