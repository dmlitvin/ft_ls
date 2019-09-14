/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:20:49 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/22 16:50:32 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_total(t_ls_list *list, int *width_link)
{
	int		out;
	nlink_t	biggest_links;

	out = 0;
	biggest_links = 0;
	while (list)
	{
		out += list->info->st_blocks;
		if (biggest_links < list->info->st_nlink)
			biggest_links = list->info->st_nlink;
		list = list->next;
	}
	*width_link = 3;
	while ((biggest_links /= 10))
		*width_link += 1;
	return (out);
}

static void	get_users_groups(t_ls_vars *ls, t_ls_list *list)
{
	int				tmp;

	ls->longest_group_name = 0;
	ls->longest_user_name = 0;
	while (list)
	{
		if ((ls->user = getpwuid(list->info->st_uid)))
		{
			tmp = (ls->user->pw_name)
			? (int)ft_strlen(ls->user->pw_name) : id_len(ls->user->pw_uid);
			if (tmp > ls->longest_user_name)
				ls->longest_user_name = tmp;
		}
		if ((ls->group = getgrgid(list->info->st_gid)))
		{
			tmp = (ls->group->gr_name)
			? (int)ft_strlen(ls->group->gr_name) : id_len(ls->group->gr_gid);
			if (tmp > ls->longest_group_name)
				ls->longest_group_name = tmp;
		}
		list = list->next;
	}
}

static void	print_user_group_size_time(t_ls_vars *ls, t_ls_list *list)
{
	ls->user = getpwuid(list->info->st_uid);
	ls->group = getgrgid(list->info->st_gid);
	if (ls->user->pw_name)
		ft_printf("%-*s ", ls->longest_user_name + 1, ls->user->pw_name);
	else
		ft_printf("%-*d ", ls->longest_user_name + 1, ls->user->pw_uid);
	if (ls->group->gr_name)
		ft_printf("%-*s", ls->longest_group_name + 1, ls->group->gr_name);
	else
		ft_printf("%-*d", ls->longest_group_name + 1, ls->group->gr_gid);
	(S_ISBLK(list->info->st_mode) || S_ISCHR(list->info->st_mode)) ?
ft_printf("%5d, %5d", major(list->info->st_rdev), minor(list->info->st_rdev))
		: ft_printf("%12d", list->info->st_size);
	ft_printf("%.7s %5.5s ", ctime(&list->info->st_mtime) + 3,
			ctime(&list->info->st_mtime) + ((list->info->st_mtime > HALF_YEAR)
			? 11 : 20));
}

static void	print_link(char *path, char *name)
{
	char			*buf;
	char			*all_path;

	buf = ft_strnew(512);
	all_path = ft_strcat(ft_strcat(ft_strcat(ft_strnew(512), path), "/"), name);
	if (readlink(all_path, buf, 512) != -1)
		ft_printf("%s -> %s\n", name, buf);
	else
		throw_error(name);
	free(all_path);
	free(buf);
}

void		print_into_lines(t_ls_list *list, int mode, char *path)
{
	t_ls_vars	ls;

	if (list)
	{
		ls.rights = ft_strnew(10);
		get_users_groups(&ls, list);
		if (list->info)
			(mode) ? ft_printf("total %d\n",
			get_total(list, &ls.wd_link))
			: get_total(list, &ls.wd_link);
		while (list)
		{
			get_rights(ls.rights, list);
			ft_printf("%s%*d ", ls.rights, ls.wd_link, list->info->st_nlink);
			print_user_group_size_time(&ls, list);
			if (list->type != DT_LNK)
				ft_printf("%s\n", list->name);
			else
				print_link(path, list->name);
			list = list->next;
		}
		free(ls.rights);
	}
}
