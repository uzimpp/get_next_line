/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:40:29 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/16 20:01:00 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	clean_lst(t_list **lst)
{
	t_list	*last;
	char	*line;
	int		i;

	last = ft_getlastnode(*lst);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	line = ft_strduplen(last->content + i);
	if (!line)
		return ;
	ft_free_lst(*lst);
	*lst = malloc(sizeof(t_list));
	if (!*lst)
	{
		free(line);
		return ;
	}
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
	while (lst != 0)
	{
		i = 0;
		while (lst->content[i] != 0)
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

void	append(t_list **lst, char *buff, t_list **current, int n)
{
	int		i;
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node || !lst)
		return ;
	node->content = malloc(sizeof(char) * (n + 1));
	node->next = NULL;
	if (!node->content)
		return ;
	i = 0;
	while (buff[i] && i < n)
	{
		node->content[i] = buff[i];
		i++;
	}
	node->content[i] = '\0';
	if (!*lst)
		*lst = node;
	else
		(*current)->next = node;
	*current = node;
}

void	readlst(int fd, t_list **lst)
{
	char	*buff;
	int		n;
	t_list	*current;

	n = 1;
	current = *lst;
	while (ft_isnotnewline(*lst) && n != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		n = (int)read(fd, buff, BUFFER_SIZE);
		if (n == -1 || (!*lst && n == 0))
		{
			if (n == -1)
				ft_free_lst(*lst);
			*lst = NULL;
			free(buff);
			return ;
		}
		buff[n] = '\0';
		append(lst, buff, &current, n);
		free(buff);
	}
}

// Max linux fd is 1024, therefore set the last lst (stash[1024] = NULL)
char	*get_next_line(int fd)
{
	static t_list	*lst[1024] = {NULL};
	char			*line;

	if (fd < 0 || 1024 <= fd || BUFFER_SIZE <= 0)
		return (NULL);
	readlst(fd, &lst[fd]);
	if (!lst[fd])
		return (NULL);
	line = NULL;
	extract_line(lst[fd], &line);
	clean_lst(&lst[fd]);
	if (!line || !line[0])
	{
		ft_free_lst(lst[fd]);
		lst[fd] = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
