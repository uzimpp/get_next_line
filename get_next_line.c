/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:40:29 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/20 12:39:02 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_lst(t_list **lst)
{
	t_list	*last;
	char	*line;
	int		i;

	if (!lst || !*lst)
		return ;
	last = ft_getlastnode(*lst);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	line = ft_strduplen(last->content + i);
	ft_free_lst(*lst);
	if (!line)
	{
		*lst = NULL;
		return ;
	}
	*lst = malloc(sizeof(t_list));
	if (!*lst)
		return ((void)free(line));
	(*lst)->content = line;
	(*lst)->next = NULL;
}

void	extract_line(t_list *lst, char **line)
{
	int	i;
	int	j;

	if (!lst)
		return ;
	ft_create_line(line, lst);
	if (!*line)
		return ;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				(*line)[j++] = lst->content[i];
				break ;
			}
			(*line)[j++] = lst->content[i++];
		}
		lst = lst->next;
	}
	(*line)[j] = '\0';
}

int	append(t_list **lst, char *buff, t_list **current, int n)
{
	int		i;
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = malloc(sizeof(char) * (n + 1));
	if (!node->content)
	{
		free(node);
		return (0);
	}
	i = -1;
	while (++i < n)
		node->content[i] = buff[i];
	node->content[i] = '\0';
	node->next = NULL;
	if (!*lst)
		*lst = node;
	else
		(*current)->next = node;
	*current = node;
	return (1);
}

int	readlst(int fd, t_list **lst)
{
	char	*buff;
	int		n;
	t_list	*current;

	n = 1;
	current = *lst;
	while (ft_isnotnewline(current) && n != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (0);
		n = (int)read(fd, buff, BUFFER_SIZE);
		if (n == -1 || (!*lst && n == 0))
		{
			free(buff);
			if (n == -1)
				ft_free_lst(*lst);
			*lst = NULL;
			return (0);
		}
		if (!append(lst, buff, &current, n))
			return (free(buff), 0);
		free(buff);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!readlst(fd, &lst))
		return (ft_free_lst(lst), lst = NULL, NULL);
	if (!lst || !lst->content)
		return (NULL);
	line = NULL;
	extract_line(lst, &line);
	if (!line)
		return (ft_free_lst(lst), lst = NULL, NULL);
	clean_lst(&lst);
	if (!line[0])
	{
		free(line);
		return (ft_free_lst(lst), lst = NULL, NULL);
	}
	return (line);
}
