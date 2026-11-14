/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eljessou <eljessou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 15:43:19 by eljessou          #+#    #+#             */
/*   Updated: 2026/11/10 21:41:49 by eljessou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

size_t	ft_strlen_bonus(const char *s);
char	*get_next_line(int fd);
t_list	*dealloc_bonus(t_list **head);
t_list	*stash_bonus(t_list *head);
char	*copy_till_bonus(t_list *head);
int		lst_size_bonus(t_list *head);
void	create_nodes_bonus(int fd, t_list **lst);
int		cought_sep_bonus(t_list *head);
int		ft_lstadd_back_bonus(t_list **lst, char *content);
void	free_all_bonus(t_list **head);

#endif
