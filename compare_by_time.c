/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparer_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:26:53 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/20 21:56:43 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long	compare_by_time(char *name1, char *name2,
			struct stat *stat1, struct stat *stat2)
{
	if (stat1->st_mtimespec.tv_sec == stat2->st_mtimespec.tv_sec)
		return (ft_strcmp(name1, name2));
	return (stat2->st_mtimespec.tv_sec - stat1->st_mtimespec.tv_sec);
}

long	compare_by_reverse_time(char *name1, char *name2,
			struct stat *stat1, struct stat *stat2)
{
	if (stat1->st_mtimespec.tv_sec == stat2->st_mtimespec.tv_sec)
		return (ft_strcmp(name2, name1));
	return (stat1->st_mtimespec.tv_sec - stat2->st_mtimespec.tv_sec);
}
