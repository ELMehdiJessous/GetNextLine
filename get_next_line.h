/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eljessou <eljessou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 15:39:36 by eljessou          #+#    #+#             */
/*   Updated: 2026/11/10 21:39:31 by eljessou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
t_list	*dealloc(t_list **head);
t_list	*stash(t_list *head);
char	*copy_till(t_list *head);
int		lst_size(t_list *head);
void	create_nodes(int fd, t_list **lst);
int		cought_sep(t_list *head);
int		ft_lstadd_back(t_list **lst, char *content);
void	free_all(t_list **head);

#endif
