/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eljessou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 17:29:41 by eljessou          #+#    #+#             */
/*   Updated: 2026/11/05 17:29:44 by eljessou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

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

int cought_sep(char *r)
{
    if (!r)
        return (0);
    while (*r)
    {
        if (*r == '\n')
            return (1);
        r++;
    }
    return (0);
}

void create_nods(int fd, t_list **lst)
{
    int     chars;
    char    *buf;

    buf = NULL;
    while (!cought_sep(buf))
    {
        buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
        if (!buf)
            return ;
        chars = read(fd,buf,BUFFER_SIZE);
        if (chars <= 0)
        {
            free(buf);
            if (chars < 0)
                free_all(lst);
            return ;
        }
        buf[chars] = '\0';
        ft_lstadd_back(lst,buf);
    }
}