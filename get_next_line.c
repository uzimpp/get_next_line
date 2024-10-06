/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:40:29 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/06 10:20:46 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	ft_create_line(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*node;
	int		i;
	int		j;

	node = malloc(sizeof(t_list));
	if (stash == NULL || node == NULL)
		return ;
	node->next = NULL;
	last = ft_getlastnode(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	node->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i) + 1));
	if (node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		node->content[j++] = last->content[i++];
	node->content[j] = '\0';
	ft_free_stash(*stash);
	*stash = node;
}

void	ft_append(t_list **stash, char *buff, int status)
{
	int		i;
	t_list	*current;
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	node -> next = NULL;
	node -> content = malloc(sizeof(char) * (status + 1));
	if (node -> content == NULL)
		return ;
	i = 0;
	while (buff[i] && i < status)
		node -> content[i++] = buff[i];
	node -> content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = node;
		return ;
	}
	current = ft_getlastnode(*stash);
	current -> next = node;
}

void	readstash(int fd, t_list **stash, int status)
{
	char	*buff;

	buff = malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!buff)
		return (NULL);
	while (ft_isnotnewline(stash) && status != 0)
	{
		status = read(fd, buff, BUFFER_SIZE);
		if (status == -1 || (stash == NULL && status == 0))
		{
			free(buff);
			return ;
		}
		buff[status] = '\0';
		ft_append(stash, status, buff);
		free(buff);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;
	int				status;

	if (fd < 0 || read(fd, &line, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = NULL;
	line = NULL;
	status = 1;
	readstash(fd, stash, &status);
	if (line == NULL)
		return (NULL);
	return (line);
}
