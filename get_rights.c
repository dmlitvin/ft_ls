/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rights.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:53:58 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/22 01:48:12 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			id_len(uid_t this)
{
	int out;

	out = 1;
	while (this /= 10)
		out++;
	return (out);
}

static char	get_file_entry(mode_t mode)
{
	if (S_ISREG(mode))
		return ('-');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISBLK(mode))
		return ('b');
	return ('-');
}

static void	check_sticky_and_set(char *str, mode_t mode)
{
	if (mode & S_ISVTX)
	{
		if (str[8] == 'x')
			str[8] = 't';
		else
			str[8] = 'T';
	}
	if (mode & S_ISUID)
	{
		str[2] = 'S';
		str[5] = 'S';
	}
	if (mode & S_ISGID)
		str[5] = 'S';
}

void		get_rights(char *str, t_ls_list *list)
{
	char	c;
	int		i;
	mode_t	mode;

	mode = list->info->st_mode;
	i = -1;
	*str++ = get_file_entry(list->info->st_mode);
	while (++i < 9)
	{
		if (!i || i == 3 || i == 6)
			c = 'x';
		else if (i == 1 || i == 4 || i == 7)
			c = 'w';
		else
			c = 'r';
		str[8 - i] = ((mode >> i) & 1) ? c : '-';
	}
	if (mode & S_ISVTX || mode & S_ISUID || mode & S_ISGID)
		check_sticky_and_set(str, mode);
}
