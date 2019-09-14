/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_flag_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:29:51 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/22 16:47:02 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			g_options;
int				g_return;

void			throw_error(char *str)
{
	char *tmp;
	char *k;

	k = strerror(errno);
	tmp = ft_strcat(ft_strcat(ft_strcat(ft_strcat(ft_strcat(ft_strnew(
			ft_strlen(str) + ft_strlen(k) + 11), "ft_ls: "), str), ": "),
					k), "\n");
	write(2, tmp, ft_strlen(tmp));
	free(tmp);
	errno = 0;
	g_return = 1;
}

static void		return_usage(char option)
{
	write(2, "ft_ls: illegal option -- ", 25);
	write(2, &option, 1);
	write(2, "\nusage: ft_ls [-RSaflrt] [file ...]\n", 36);
	g_return = 1;
	exit(1);
}

static void		parse_option(char c)
{
	if (c == 'a')
		g_options |= FLAG_HIDDEN;
	else if (c == 'l')
		g_options |= FLAG_LW;
	else if (c == 'r')
		g_options |= FLAG_REVERSE;
	else if (c == 'R')
		g_options |= FLAG_RECURSIVE;
	else if (c == 't')
		g_options |= FLAG_TIME_SORT;
	else if (c == 'S')
		g_options |= FLAG_SIZE_SORT;
	else
	{
		g_options |= FLAG_HIDDEN;
		g_options |= FLAG_F;
	}
}

int				ft_skip_make_flags(int ac, char **av)
{
	int k;
	int arg_nb;

	arg_nb = 0;
	while (arg_nb < ac && av[arg_nb][0] == '-' && av[arg_nb][1])
	{
		k = 0;
		while (av[arg_nb][++k])
		{
			if (av[arg_nb][k] == 'a' || av[arg_nb][k] == 'l'
			|| av[arg_nb][k] == 'f' || av[arg_nb][k] == 'r'
			|| av[arg_nb][k] == 'R' || av[arg_nb][k] == 't'
			|| av[arg_nb][k] == 'S')
				parse_option(av[arg_nb][k]);
			else
				return_usage(av[arg_nb][k]);
		}
		arg_nb++;
	}
	return (arg_nb);
}
