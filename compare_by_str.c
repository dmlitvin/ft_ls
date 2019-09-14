/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 22:03:38 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/20 22:07:47 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long	compare_by_str(char *name1, char *name2,
					struct stat *stat1, struct stat *stat2)
{
	(void)stat1;
	(void)stat2;
	return (ft_strcmp(name1, name2));
}

long	compare_by_reverse_str(char *name1, char *name2,
					struct stat *stat1, struct stat *stat2)
{
	(void)stat1;
	(void)stat2;
	return (ft_strcmp(name2, name1));
}
