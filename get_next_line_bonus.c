/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eljessou <eljessou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 21:50:55 by eljessou          #+#    #+#             */
/*   Updated: 2026/11/10 21:54:27 by eljessou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	lst_size_bonus(t_list *head)
{
	int	size;
	int	i;

	size = 0;
	while (head)
	{
		i = 0;
		while (head->content[i])
		{
			if (head->content[i] == '\n')
			{
				size++;
				return (size);
			}
			i++;
			size++;
		}
		head = head->next;
	}
	return (size);
}

char	*copy_till_bonus(t_list *head)
{
	char	*p;
	int		i;
	int		k;

	p = malloc((lst_size_bonus(head) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	k = 0;
	while (head)
	{
		i = 0;
		while (head->content[i])
		{
			p[k++] = head->content[i];
			if (head->content[i] == '\n')
			{
				p[k] = '\0';
				return (p);
			}
			i++;
		}
		head = head->next;
	}
	*(p + k) = '\0';
	return (p);
}

t_list	*stash_bonus(t_list *head)
{
	char	*buf;
	int		i;
	int		k;

	i = 0;
	k = 0;
	while (head->content[i] && head->content[i] != '\n')
		i++;
	i += (head->content[i] == '\n');
	if (head->content[i] == '\0')
		return (free(head->content), free(head), NULL);
	buf = malloc(sizeof(char) * (ft_strlen_bonus(head->content) - i + 1));
	if (!buf)
		return (NULL);
	while (head->content[i])
		*(buf + k++) = head->content[i++];
	*(buf + k) = '\0';
	free(head->content);
	head->content = buf;
	head->next = NULL;
	return (head);
}

t_list	*dealloc_bonus(t_list **head)
{
	t_list	*next;
	int		i;

	if (!head || !*head)
		return (NULL);
	while (*head)
	{
		i = 0;
		while ((*head)->content[i] && (*head)->content[i] != '\n')
			i++;
		if ((*head)->content[i] == '\n')
			return (stash_bonus(*head));
		next = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = next;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*head[MAX_FD];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	create_nodes_bonus(fd, &head[fd]);
	if (!head[fd])
		return (NULL);
	line = copy_till_bonus(head[fd]);
	if (!line)
	{
		free_all_bonus(&head[fd]);
		return (NULL);
	}
	head[fd] = dealloc_bonus(&head[fd]);
	return (line);
}
