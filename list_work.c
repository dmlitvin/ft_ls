/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 21:29:43 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/22 02:31:41 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

long			(*g_comparer)(char*, char*, struct stat*, struct stat*);

static t_ls_list	*get_new_list(char *name, struct stat *info,
		t_ls_list *the_next, char type)
{
	t_ls_list *out;

	out = (t_ls_list*)ft_memalloc(sizeof(t_ls_list));
	out->next = the_next;
	out->name = name;
	out->type = type;
	if (info)
		out->info = ft_memcpy(malloc(sizeof(*info)), info, sizeof(*info));
	return (out);
}

void				add_list(t_ls_list **head, char *name,
		struct stat *info, char type)
{
	t_ls_list	*tmp;

	if (!*head || g_comparer(name, (*head)->name, info, (*head)->info) < 0)
		*head = get_new_list(name, info, *head, type);
	else
	{
		tmp = *head;
		while (tmp->next && (g_comparer(name, tmp->next->name,
				info, tmp->next->info) > 0))
			tmp = tmp->next;
		tmp->next = get_new_list(name, info, tmp->next, type);
	}
}

void				clean_list(t_ls_list *head)
{
	if (!head)
		return ;
	if (head->next)
		clean_list(head->next);
	if (head->info)
		free(head->info);
	free(head->name);
	free(head);
}
