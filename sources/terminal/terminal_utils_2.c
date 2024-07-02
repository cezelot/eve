/* ************************************************************************** */
/*                                                                            */
/*   terminal_utils_2.c                                                       */
/*                                                                            */
/*   Created: 2024/05/31 12:49:14 by cezelot                                  */
/*   Updated: 2024/05/31 13:35:27 by cezelot                                  */
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

int	get_nav_key(char *seq)
{
	if (seq[1] == '1' || seq[1] == '7')
		return (HOME_KEY);
	else if (seq[1] == '3')
		return (DEL_KEY);
	else if (seq[1] == '4' || seq[1] == '8')
		return (END_KEY);
	else if (seq[1] == '5')
		return (PAGE_UP);
	else if (seq[1] == '6')
		return (PAGE_DOWN);
	return (0);
}
