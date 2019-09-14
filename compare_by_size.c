/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:04:11 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/22 02:39:00 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long	compare_by_size(char *name1, char *name2,
				struct stat *stat1, struct stat *stat2)
{
	if (stat1->st_size == stat2->st_size)
		return (ft_strcmp(name1, name2));
	return (stat2->st_size - stat1->st_size);
}

long	compare_by_reverse_size(char *name1, char *name2,
				struct stat *stat1, struct stat *stat2)
{
	if (stat1->st_size == stat2->st_size)
		return (ft_strcmp(name2, name1));
	return (stat1->st_size - stat2->st_size);
}

long	lazy_compare(char *name1, char *name2,
		struct stat *stat1, struct stat *stat2)
{
	(void)name1;
	(void)name2;
	(void)stat1;
	(void)stat2;
	return (1);
}
