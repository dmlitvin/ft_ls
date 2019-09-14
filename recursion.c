/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 16:40:26 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/22 16:28:54 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char				g_options;
void				(*g_print_files)(t_ls_list*, int mode, char *path);

static t_ls_list	*get_next_dir(t_ls_list *list)
{
	while (list && list->type != DT_DIR)
		list = list->next;
	if (list && ((list->name[0] == '.' && !list->name[1])
		|| (list->name[0] == '.' && list->name[1] == '.'
			&& !list->name[2])))
		return (get_next_dir(list->next));
	return (list);
}

static struct stat	get_stat(char *path, struct dirent *this)
{
	char		*all_path;
	struct stat	the_stat;

	all_path = ft_strcat(ft_strcat(ft_strcat(ft_strnew(ft_strlen(path)
		+ ft_strlen(this->d_name) + 1), path), "/"), this->d_name);
	if (this->d_type != DT_LNK)
	{
		if (stat(all_path, &the_stat) == -1)
			throw_error(this->d_name);
	}
	else
	{
		if (lstat(all_path, &the_stat) == -1)
			throw_error(this->d_name);
	}
	free(all_path);
	return (the_stat);
}

static t_ls_list	*get_files_here(char *path)
{
	DIR				*directory;
	t_ls_list		*out;
	struct dirent	*this;
	struct stat		*info;
	struct stat		the_stat;

	out = NULL;
	info = (IS_TIME_SORT || IS_LW || IS_SIZE_SORT) ? &the_stat : NULL;
	if ((directory = opendir(path)))
	{
		while ((this = readdir(directory)))
			if (this->d_name[0] != '.' || IS_HIDDEN)
			{
				if (IS_TIME_SORT || IS_LW || IS_SIZE_SORT)
					the_stat = get_stat(path, this);
				add_list(&out, ft_strdup(this->d_name), info, this->d_type);
			}
		if (errno)
			throw_error(path);
		closedir(directory);
	}
	else
		throw_error(path);
	return (out);
}

void				list_dir_info(char *dirname)
{
	char		new_path[BUFF_SIZE + ft_strlen(dirname)];
	t_ls_list	*files_here;
	t_ls_list	*d_move;

	files_here = get_files_here(dirname);
	g_print_files(files_here, 1, dirname);
	d_move = (IS_RECURSIVE) ? get_next_dir(files_here) : NULL;
	while (d_move)
	{
		ft_memset(new_path, 0, BUFF_SIZE + ft_strlen(dirname));
		ft_strcat(new_path, dirname);
		if (!(*dirname == '/' && !dirname[1]))
			ft_strcat(ft_strcat(new_path, "/"), d_move->name);
		else
			ft_strcat(new_path, d_move->name);
		write(1, "\n", 1);
		write(1, new_path, ft_strlen(new_path));
		write(1, ":\n", 2);
		list_dir_info(new_path);
		d_move = get_next_dir(d_move->next);
		ft_strclr(ft_strrchr(new_path, '/'));
	}
	clean_list(files_here);
}
