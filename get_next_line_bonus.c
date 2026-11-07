/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eljessou <eljessou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 21:50:55 by eljessou          #+#    #+#             */
/*   Updated: 2026/11/07 23:15:54 by eljessou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

int lst_size(t_list *head)
{
    int size;
    int i;

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

char *copy_till(t_list *head)
{
    char    *p;
    int     i;
    int     k;
    
    p = malloc((lst_size(head) + 2) * sizeof(char));
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

t_list  *stash(t_list *head)
{
    char    *buf;
    int     i;
    int     k;

    i = 0;
    k = 0;
    while (head->content[i] && head->content[i] != '\n')
        i++;
    if (head->content[i] == '\n')
        i++;
    if (head->content[i] == '\0')
	{
		t_list *next = head->next;
		free(head->content);
		free(head);
		return (next);
	}
    buf = malloc(sizeof(char) * (ft_strlen(head->content) - i + 1));
    if (!buf)
        return (NULL);
    while (head->content[i])
        *(buf + k++) = head->content[i++];
    *(buf + k) = '\0';
    free(head->content);
    head->content = buf;
    return (head);
}

t_list	*dealloc(t_list **head)
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
			return (stash(*head));
		next = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = next;
	}
	return (NULL);
}

char *get_next_line_bonus(int fd)
{
    static  t_list  *head[MAX_FD];
    char            *line;

    if (fd < 0 || BUFFER_SIZE == 0 || (0 > read(fd,0,0)))
        return (NULL);
    create_nods(fd, &head[fd]);
    if (!head[fd])
        return (NULL);
    line = copy_till(head[fd]);
    if (!line)
    {
        free_all(&head[fd]);
        return (NULL);
    }
    head[fd] = dealloc(&head[fd]);
    return (line);
}