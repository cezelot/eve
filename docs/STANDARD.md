# Coding Standard

Here are the set of rules/guidelines used when writing source codes of this
project.

**Table of Content:**
 - [Denomination](#denomination)
 - [Formatting](#formatting)
 - [Functions](#functions)
 - [Typedef, struct, enum and union](#typedef,-struct,-enum-and-union)
 - [Headers](#headers)
 - [The license notice](#the-license-notice)
 - [Macros and Pre-processors](#macros-and-pre-processors)
 - [Forbidden stuff](#forbidden-stuff)
 - [Comments](#comments)
 - [Files](#files)

## Denomination

 - A structure’s name must start by `s_`.
 - A typedef’s name must start by `t_`.
 - A union’s name must start by `u_`.
 - An enum’s name must start by `e_`.
 - A global’s name must start by `g_`.
 - Variables and functions names can only contain lowercases, digits and '_' (snake_case).
 - Files and directories names can only contain lowercases, digits and '_'
   (excluding documentation files, e.g., README.md, CHANGELOG.md, ...).
 - Characters that aren’t part of the standard ASCII table are forbidden.
 - Variables, functions, and any other identifier must use snake case. No capital letters,
   and each word separated by an underscore.
 - All identifiers (functions, macros, types, variables, etc.) must be in English.
 - Objects (variables, functions, macros, types, files or directories) must have the most
   explicit or most mnemonic names as possible.
 - Using global variables that are not marked `const` and `static` is forbidden.

## Formatting

 - You must indent your code with 4-space tabulations. This is not the same as 4
   average spaces, we’re talking about real tabulations here.
 - Try to keep each function less than 26 lines, not counting the function’s own
   curly brackets and the comments (if there are any).
 - Each line must be at most 80 columns wide, comments included. Warning: a
   tabulation doesn’t count as a column, but as the number of spaces it represents.
 - Each function must be separated by a newline. Any comment or preprocessor
   instruction can be right above the function. The newline is after the previous
   function.
 - One instruction per line.
 - An empty line must be empty: no spaces or tabulations.
 - A line can never end with spaces or tabulations.
 - You can never have two consecutive spaces.
 - You need to start a new line after each curly bracket or end of control structure.
 - Unless it’s the end of a line, each comma or semi-colon must be followed by a space.
 - Each operator or operand must be separated by one - and only one - space.
 - Each C keyword must be followed by a space, except for keywords for types (such
   as `int`, `char`, `float`, etc.), as well as `sizeof()`.
 - Each variable declaration must be indented on the same column for its scope.
 - The asterisks that go with pointers must be stuck to variable names.
 - One single variable declaration per line.
 - Declaration and an initialisation cannot be on the same line, except for global
   variables, static variables, and constants.
 - Declarations must be at the beginning of a function.
 - In a function, you must place an empty line between variable declarations and the
   remaining of the function. No other empty lines are allowed in a function.
 - Multiple assignments are strictly forbidden.
 - You may add a new line after an instruction or control structure, but you’ll have
   to add an indentation with brackets or assignment operator. Operators must be at
   the beginning of a line.
 - Control structures (`if`, `while..`) must have braces, unless they contain a single line.
 - Braces following functions, declarators or control structures must be preceded and
   followed by a newline.

General example:

```c
int g_global;

typedef struct  s_struct
{
	char    *str;
    int	    i;
}   t_struct;

struct	s_other_struct;

int	main(void)
{
    int     i;
    char    c;

    return (i);
}
```

## Functions

 - A function can take 4 named parameters maximum.
 - A function that doesn’t take arguments must be explicitly prototyped with the
   keyword `void` as the argument.
 - Parameters in functions’ prototypes must be named.
 - Each function must be separated from the next by an empty line.
 - You can’t declare more than 5 variables per function.
 - Return of a function has to be between parenthesis.
 - Each function must have a single tabulation between its return type and its name.

```c
int func2(char, *message, int len, char c)
{
    return (nb);
}

int func(void)
{
    return ;
}
```

## Typedef, struct, enum and union

 - Add a tabulation when declaring a struct, enum or union.
 - When declaring a variable of type struct, enum or union, add a single space in the
   type.
 - When declaring a struct, union or enum with a typedef, all indentation rules apply.
 - Typedef name must be preceded by a tab.
 - You must indent all structures’ names on the same column for their scope.
 - You cannot declare a structure in a .c file.

## Headers

 - The things allowed in header files are: header inclusions (system or not), declara-
   tions, defines, prototypes and macros.
 - All includes must be at the beginning of the file.
 - You cannot include a C file.
 - Header files must be protected from double inclusions. If the file is foo.h, its
   bystander macro is `FOO_H`.
 - Unused header inclusions (.h) are forbidden.
 - All header inclusions must be justified in a .c file as well as in a .h file.

```c
#ifndef FOO_H
# define FOO_H

# include <stdlib.h>
# include <stdio.h>
# define VERSION "0.1.0"

typedef struct s_config
{
	char    *color;
	int     tabstop;
}           t_conf;

void    init(t_conf *config);
void    die(const char *format, ...);

#endif /* FOO_H */
```

## The license notice

 - Every .c and .h file should start with the header below.
 - If you modify a .c or .h file, you must update the date of the modification
   and the name of its author. Please also add your name in the copyright notice, i.e.,
   `Copyright (C) 2024 Jane Doe, Your Name`.

```c
/* ************************************************************************** */
/*                                                                            */
/*   <filename> - <optional description>                                      */
/*                                                                            */
/*   Created: 2024/07/17 00:00:01 by <name>                                   */
/*   Updated: 2024/07/17 00:01:00 by <name>                                   */
/*                                                                            */
/*   Copyright (C) 2024 <name>                                                */
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
```

## Macros and Pre-processors

 - Preprocessor constants (or `#define`) you create must be used only for literal and
   constant values.
 - Multiline macros are forbidden.
 - Macro names must be all uppercase.
 - You must indent characters following `#if`, `#ifdef` or `#ifndef`.
 - Preprocessor instructions are forbidden outside of global scope.

## Forbidden stuff

 - You’re not allowed to use:
   - `do...while`
   - `goto`
 - Ternary operators such as ‘?’.
 - VLAs - Variable Length Arrays.

## Comments

Comments are not mandatory but encouraged.

 - Write the comments in English.
 - Comments must be at the end of a line, or on their own line
 - Put two spaces after the end of a sentence in your comments, so that the Emacs
   sentence commands will work. Also, please write complete sentences and capitalize
   the first word.
 - Put a comment on top of each function saying what the function does, what sorts of
   arguments it gets, and what the possible values of arguments mean and are used for.
   Also explain the significance of the return value, if there is one.

```c
/* The comment on a function is much clearer if you use the argument names to speak
   about the argument values. The variable name itself should be lower case, but write it in
   upper case when you are speaking about the value rather than the variable itself, i.e.,
   “the inode number NODENUM” rather than “an inode”.  */
void    func(int nodenum)
{
}
```

## Files

 - You cannot include a .c file.
