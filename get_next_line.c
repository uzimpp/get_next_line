/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:40:29 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/16 20:10:55 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_lst(t_list **lst)
{
	t_list	*current;
	char	*line;
	int		i;

	current = ft_getcurrentnode(*lst);
	i = 0;
	while (current->content[i] && current->content[i] != '\n')
		i++;
	if (current->content[i] == '\n')
		i++;
	line = ft_strduplen(current->content + i);
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
	while (ft_isnotnewline(current) && n != 0)
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

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readlst(fd, &lst);
	if (!lst)
		return (NULL);
	line = NULL;
	extract_line(lst, &line);
	clean_lst(&lst);
	if (!line || !line[0])
	{
		ft_free_lst(lst);
		lst = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
