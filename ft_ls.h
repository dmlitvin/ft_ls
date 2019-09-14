/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <dmlitvin@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:18:05 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/09/13 20:43:13 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft/include/libft.h"
# include <errno.h>
# include <time.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include <sys/types.h>
# include <sys/dirent.h>
# include <sys/stat.h>

/*
** Defines for flags.
*/

# define HALF_YEAR			15768000

# define FLAG_RECURSIVE		(1 << 0)
# define FLAG_HIDDEN 		(1 << 1)
# define FLAG_REVERSE 		(1 << 2)
# define FLAG_TIME_SORT 	(1 << 3)
# define FLAG_LW			(1 << 4)
# define FLAG_F				(1 << 5)
# define FLAG_SIZE_SORT		(1 << 6)

# define IS_RECURSIVE		(g_options & FLAG_RECURSIVE)
# define IS_HIDDEN			(g_options & FLAG_HIDDEN)
# define IS_REVERSE			(g_options & FLAG_REVERSE)
# define IS_TIME_SORT		(g_options & FLAG_TIME_SORT)
# define IS_SIZE_SORT		(g_options & FLAG_SIZE_SORT)
# define IS_LW				(g_options & FLAG_LW)
# define IS_F				(g_options & FLAG_F)

/*
** Structures for browsing files.
*/

typedef struct				s_ls_list
{
	struct s_ls_list		*next;
	struct stat				*info;
	char					*name;
	char					type;
}							t_ls_list;

typedef struct				s_ls_vars
{
	char					*rights;
	int						wd_link;
	int						longest_user_name;
	int						longest_group_name;
	struct passwd			*user;
	struct group			*group;
}							t_ls_vars;

/*
** Global_variable for flags (as we have to manage not more than 8 options,
** char type variable is enough), pointer to comparer function and pointer
** to function that prints files information taking a list of that files.
*/

extern char					g_options;
extern long					(*g_comparer)(char*, char*,
		struct stat*, struct stat*);
extern void					(*g_print_files)(t_ls_list*, int mode, char *path);
extern int					g_return;

/*
** Functions' prototypes.
*/
int							ft_skip_make_flags(int ac, char **av);
long						compare_by_time(char *name1, char *name2,
		struct stat *stat1, struct stat *stat2);
long						compare_by_reverse_time(char *name1, char *name,
		struct stat *stat1, struct stat *stat2);
long						compare_by_reverse_str(char *name1, char *name2,
		struct stat *stat1, struct stat *stat2);
long						compare_by_str(char *name1, char *name,
		struct stat *stat1, struct stat *stat2);
long						compare_by_size(char *name1, char *name2,
		struct stat *stat1, struct stat *stat2);
long						compare_by_reverse_size(char *name1, char *name2,
		struct stat *stat1, struct stat *stat2);
long						lazy_compare(char *name1, char *name2,
		struct stat *stat1, struct stat *stat2);
void						list_dir_info(char *path);
void						throw_error(char *str);
void						add_list(t_ls_list **head,
		char *name, struct stat *info, char type);
void						clean_list(t_ls_list *head);
void						simple_print(t_ls_list *list, int mode, char *path);
int							id_len(uid_t this);
void						print_into_lines(t_ls_list *list,
		int mode, char *path);
void						get_rights(char *str, t_ls_list *list);

#endif
