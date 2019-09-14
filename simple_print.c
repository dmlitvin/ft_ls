/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:56:15 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/22 01:16:28 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		simple_print(t_ls_list *list, int mode, char *path)
{
	(void)path;
	(void)mode;
	while (list)
	{
		ft_printf("%s\n", list->name);
		list = list->next;
	}
}
