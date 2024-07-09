/* ************************************************************************** */
/*                                                                            */
/*   append_buffer.c - dynamic string routines                                */
/*                                                                            */
/*   Created: 2023/12/18 14:16:44 by cezelot                                  */
/*   Updated: 2024/06/20 11:02:16 by cezelot                                  */
/*                                                                            */
/*   Copyright (C) 2024 Ismael B. Hamed                                       */
/*                                                                            */
/*   This file is part of eve.                                                */
/*                                                                            */
/*   eve is free software: you can redistribute it and/or modify              */
/*   it under the terms of the GNU General Public License as published by     */
/*   the Free Software Foundation, either version 3 of the License, or        */
/*   (at your option) any later version.                                      */
/*                                                                            */
/*   eve is distributed in the hope that it will be useful,                   */
/*   but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            */
/*   GNU General Public License for more details.                             */
/*                                                                            */
/*   You should have received a copy of the GNU General Public License        */
/*   along with eve.  If not, see <https://www.gnu.org/licenses/>.            */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/eve.h"

/* Add STR to the content of the dynamic string ABUF.  */
void	abuf_append(t_abuf *abuf, const char *str, int len)
{
	char	*new_buf;

	new_buf = realloc(abuf->buf, abuf->len + len);
	if (new_buf == NULL)
		return ;
	memcpy(&new_buf[abuf->len], str, len);
	abuf->buf = new_buf;
	abuf->len += len;
}

void	abuf_free(t_abuf *abuf)
{
	free(abuf->buf);
}
