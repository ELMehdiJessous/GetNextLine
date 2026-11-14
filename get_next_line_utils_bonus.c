/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eljessou <eljessou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 21:51:46 by eljessou          #+#    #+#             */
/*   Updated: 2026/11/10 21:42:38 by eljessou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_all_bonus(t_list **head)
{
	t_list	*next;

	while (head && *head)
	{
		next = (*head)->next;
		free((*head)->content);
		(*head)->content = NULL;
		(*head)->next = NULL;
		free(*head);
		(*head) = next;
	}
	head = NULL;
}

int	ft_lstadd_back_bonus(t_list **lst, char *content)
{
	t_list	*curr;
	t_list	*p;

	if (!lst || !content)
		return (0);
	p = malloc(sizeof(t_list));
	if (!p)
	{
		free(content);
		return (0);
	}
	p->content = content;
	p->next = NULL;
	if (!*lst)
	{
		*lst = p;
		return (1);
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = p;
	return (1);
}

size_t	ft_strlen_bonus(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	cought_sep_bonus(t_list *head)
{
	int	i;

	while (head)
	{
		i = 0;
		while (head->content[i])
		{
			if (head->content[i] == '\n')
				return (1);
			i++;
		}
		head = head->next;
	}
	return (0);
}

void	create_nodes_bonus(int fd, t_list **lst)
{
	ssize_t	chars;
	char	*buf;

	buf = NULL;
	while (!cought_sep_bonus(*lst))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return ;
		chars = read(fd, buf, BUFFER_SIZE);
		if (chars <= 0)
		{
			free(buf);
			if (chars < 0)
				free_all_bonus(lst);
			return ;
		}
		buf[chars] = '\0';
		if (!ft_lstadd_back_bonus(lst, buf))
		{
			free_all_bonus(lst);
			return ;
		}
	}
}
