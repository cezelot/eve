/* ************************************************************************** */
/*                                                                            */
/*   input_3.c                                                                */
/*                                                                            */
/*   Created: 2024/05/30 17:10:05 by cezelot                                  */
/*   Updated: 2024/08/17 18:47:48 by alberrod                                 */
/*                                                                            */
/*   Copyright (C) 2024 Ismael Benjara, Alberto Rodriguez                     */
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

#include "../eve.h"

static void
pending_to_handle(t_env *env, int key)
{
	(void)key;
	(void)env;
}

/* Sort the keymap using the quicksort algorithm.  */
static void
quicksort_keymap(t_key_map *keymap, int start, int end)
{
	if (start >= end) {
		return ;
	}
	int	pivot = keymap[end].key;
	int	idx = start;

	for (int i = start; i < end; ++i) {
		if (keymap[i].key < pivot) {
			t_key_map tmp = keymap[i];
			keymap[i] = keymap[idx];
			keymap[idx] = tmp;
			++idx;
		}
	}
	t_key_map tmp = keymap[idx];
	keymap[idx] = keymap[end];
	keymap[end] = tmp;
	quicksort_keymap(keymap, start, idx -1);
	quicksort_keymap(keymap, idx + 1, end);
}

/* Run the handler for the given key if it exists in the keymap.  */
static int
run_key(t_key_map *keymap, int size, t_env *env, int key)
{
	int	mid;
	int	low = 0;
	int	high = size - 1;

	while (low <= high) {
		mid = low + (high - low) / 2;
		if (keymap[mid].key > key) {
			high = mid - 1;
		} else if (keymap[mid].key < key) {
			low = mid + 1;
		} else {
			keymap[mid].handler(env, key);
			return (1);
		}
	}
	return (0);
}

/* Builds a static keymap, sorts it, and tries to execute the given key.
   Return 1 if success and 0 if the key was not found.  */
int
handle_special_keys(t_env *env, int key)
{
	static t_key_map keymap[] = {
		{CTRL_S, handle_signals},
		{CTRL_F, handle_signals},
		{CTRL_Q, handle_signals},
		{CTRL_L, pending_to_handle},
		{ESC, pending_to_handle},
		{CTRL_H, handle_deletion_keys},
		{BACKSPACE, handle_deletion_keys},
		{DEL_KEY, handle_deletion_keys},
		{HOME_KEY, handle_position_keys},
		{END_KEY, handle_position_keys},
		{PAGE_UP, handle_page_keys},
		{PAGE_DOWN, handle_page_keys},
		{ARROW_UP, move_cursor},
		{ARROW_DOWN, move_cursor},
		{ARROW_LEFT, move_cursor},
		{ARROW_RIGHT, move_cursor},
	};
	static int	is_map_sorted = 0;
	int		size = sizeof(keymap) / sizeof(t_key_map);

	if (!is_map_sorted) {
		quicksort_keymap(keymap, 0, size - 1);
		is_map_sorted = 1;
	}
	return (run_key(keymap, size, env, key));
}
