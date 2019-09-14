/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 13:11:08 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/22 17:25:32 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			g_options;
void			(*g_print_files)(t_ls_list*, int mode, char *path);
int				g_return;

static void		get_comparer(void)
{
	if (IS_F)
		g_comparer = lazy_compare;
	else
	{
		g_comparer = (IS_REVERSE) ? compare_by_reverse_str : compare_by_str;
		if (IS_TIME_SORT)
			g_comparer = (IS_REVERSE)
					? compare_by_reverse_time : compare_by_time;
		if (IS_SIZE_SORT)
			g_comparer = (IS_REVERSE)
					? compare_by_reverse_size : compare_by_size;
	}
}

static void		parse_link(char *name, t_ls_list **dirs, t_ls_list **files,
		struct stat *info)
{
	if (IS_LW && name[ft_strlen(name) - 1] != '/')
		add_list(files, ft_strdup(name), info, 0);
	else
		add_list(dirs, ft_strdup(name), info, 0);
}

static void		show_arguments(int ac, t_ls_list *files, t_ls_list *dirs)
{
	t_ls_list *tmp;

	if (ac == 1 && dirs)
		list_dir_info(dirs->name);
	else
	{
		g_print_files(files, 0, ".");
		tmp = dirs;
		while (tmp)
		{
			ft_printf("\n%s:\n", tmp->name);
			list_dir_info(tmp->name);
			tmp = tmp->next;
		}
	}
	if (files)
		clean_list(files);
	if (dirs)
		clean_list(dirs);
}

static void		run_ft_ls(int ac, char **av)
{
	struct stat	this_file;
	t_ls_list	*dirs;
	t_ls_list	*files;
	int			i;

	i = -1;
	dirs = NULL;
	files = NULL;
	while (++i < ac)
	{
		if (lstat(av[i], &this_file) == -1)
			throw_error(av[i]);
		else if (S_ISLNK(this_file.st_mode))
			parse_link(av[i], &dirs, &files, &this_file);
		else if (S_ISDIR(this_file.st_mode))
			add_list(&dirs, ft_strdup(av[i]), &this_file, 0);
		else
			add_list(&files, ft_strdup(av[i]), &this_file, 0);
	}
	show_arguments(ac, files, dirs);
}

int				main(int ac, char **av)
{
	char	*dot;
	int		arg_nb;

	dot = ".";
	g_options = 0;
	g_return = 0;
	arg_nb = ft_skip_make_flags(ac - 1, av + 1) + 1;
	get_comparer();
	g_print_files = (IS_LW)
			? print_into_lines : simple_print;
	(ac - arg_nb) ? run_ft_ls(ac - arg_nb, av + arg_nb)
		: (run_ft_ls(1, &dot));
	return (g_return);
}
