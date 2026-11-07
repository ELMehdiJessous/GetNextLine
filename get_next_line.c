/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eljessou <eljessou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 17:29:09 by eljessou          #+#    #+#             */
/*   Updated: 2026/11/06 19:12:28 by eljessou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_lstadd_back(t_list **lst, char *content)
{
	t_list	*curr;
    t_list	*p;

	if (!lst || !content)
		return ;
	p = malloc(sizeof(t_list));
	if (!p)
    {
        free(content);
		return ;
    }
	p->content = content;
	p->next = NULL;
	if (!*lst)
	{
		*lst = p;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = p;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int cought_sep(t_list **head)
{
    int     i;
    t_list  *curr;

    if (!head)
        return (0);
    curr = *head;
    while (curr)
    {
        i = 0;
        while (curr->content[i])
        {
            if (curr->content[i] == '\n')
                return (1);
            i++;
        }
        curr = curr->next;
    }
    return (0);
}

void create_nods(int fd, t_list **lst)
{
    int     chars;
    char    *buf;

    while ((!cought_sep(lst)))
    {
        buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!buf)
            return;
        chars = read(fd,buf,BUFFER_SIZE);
        if (chars <= 0)
        {
            free(buf);
            if (chars < 0)
            {
                free_all(lst);
                return;
            }
            return ;
        }
        buf[chars] = '\0';
        ft_lstadd_back(lst,buf);
    }
}

int lst_size(t_list *head)
{
    int size;
    int i;

    size = 0;
    while (head)
    {
        i = 0;
        while (head->content[i] && head->content[i] != '\n')
        {
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
        while (head->content[i] && head->content[i] != '\n')
            *(p + k++) = head->content[i++];
        if (head->content[i] == '\n')
        {
            *(p + k++) = '\n';
            break;
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

void free_all(t_list **head)
{
    t_list  *next;

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

char *get_next_line(int fd)
{
    static  t_list  *head;
    char            *line;
    t_list          *tmp;

    if (fd < 0 || BUFFER_SIZE == 0 || (0 > read(fd,0,0)))
        return (NULL);
    create_nods(fd, &head);
    while (head && head->content[0] == '\0')
    {
        tmp = head;
        head = head->next;
        free(tmp->content);
        free(tmp);
    }
    if (!head)
        return (NULL);
    line = copy_till(head);
    if (!line)
    {
        free_all(&head);
        return (NULL);
    }
    head = dealloc(&head);
    return (line);
}