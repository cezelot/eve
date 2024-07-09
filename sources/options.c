/* ************************************************************************** */
/*                                                                            */
/*   options.c - parse command-line options                                   */
/*                                                                            */
/*   Created: 2024/06/29 14:34:26 by cezelot                                  */
/*   Updated: 2024/07/02 18:33:47 by cezelot                                  */
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

/* Display usage information.  */
static void	show_help(void)
{
	printf("Usage: %s [options] [file]\n", PROGRAM_NAME);
	puts("\nOptions:\n"
		"  -h, --help                 display this help and exit\n"
		"  -v, --version              output version information and exit");
}

/* Display the version and license.  */
static void	show_version(void)
{
	printf("%s %s\n", PROGRAM_NAME, EVE_VERSION);
	puts("Copyright (C) 2024 Ismael B. Hamed");
	puts("License GPLv3+: GNU GPL version 3 or later "
		"<https://gnu.org/licenses/gpl.html>\n"
		"This is free software: you are free to change and redistribute it.\n"
		"There is NO WARRANTY, to the extent permitted by law.");
}

/* Map the command-line option C and exit.  */
static void	scan_option(int c)
{
	if (c == 'h')
	{
		show_help();
		exit(0);
	}
	else if (c == 'v')
	{
		show_version();
		exit(0);
	}
	else if (c == '?')
	{
		printf("Try '%s --help' for more information.\n", PROGRAM_NAME);
		exit(1);
	}
}

void	parse_options(int ac, char **av, int *option_index)
{
	int						c;
	static struct option	long_options[] = {
	{"help", no_argument, 0, 'h'},
	{"version", no_argument, 0, 'v'},
	{0, 0, 0, 0}
	};

	c = '\0';
	while (1)
	{
		*option_index = 0;
		c = getopt_long(ac, av, "hv", long_options, option_index);
		if (c == -1)
			break ;
		scan_option(c);
	}
	*option_index = optind;
}
