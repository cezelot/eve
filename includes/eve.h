/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eve.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhamed <bhamed@student.42antananarivo.mg>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:17:10 by bhamed            #+#    #+#             */
/*   Updated: 2023/12/29 17:21:15 by bhamed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVE_H
# define EVE_H

# define EVE_VERSION "0.0.1"
# define _DEFAULT_SOURCE

# include <ctype.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <unistd.h>

enum e_editor_key
{
	ARROW_LEFT = 1000,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
	DEL_KEY,
	HOME_KEY,
	END_KEY,
	PAGE_UP,
	PAGE_DOWN
};

typedef struct s_erow
{
	int		size;
	char	*chars;
}			t_erow;

typedef struct s_editor_config
{
	int		cx;
	int		cy;
	int		screenrows;
	int		screencols;
	int		numrows;
	t_erow	row;
}			t_env;

typedef struct s_abuf
{
	char	*buf;
	int		len;
}			t_abuf;

void	editor_open(t_env *env, char *filename);
void	editor_refresh_screen(t_env *env);
void	die(const char *str);
void	disable_raw_mode(void);
void	enable_raw_mode(void);
void	editor_process_keypress(t_env *env);
int		editor_read_key(void);
int		get_window_size(int *rows, int *cols);
int		read_escape_sequences(void);
int		read_key(int *pi, char *pc);

#endif
