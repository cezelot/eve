/* ************************************************************************** */
/*                                                                            */
/*   row_operations_2.c                                                       */
/*                                                                            */
/*   Created: 2024/07/22 11:34:50 by cezelot                                  */
/*   Updated: 2024/07/22 11:36:41 by cezelot                                  */
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

#include "../../includes/eve.h"

/* Replace a tab by TAB_STOP spaces characters.  */
void	render_tab(char *render, int *index)
{
	render[(*index)++] = ' ';
	while (*index % TAB_STOP)
		render[(*index)++] = ' ';
}
