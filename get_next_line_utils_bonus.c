/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:40:29 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/06 16:11:33 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_isnotnewline(t_list *stash)
{
	int		i;
	t_list	*current;

	if (stash == NULL)
		return (1);
	i = 0;
	current = ft_getlastnode(stash);
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

t_list	*ft_getlastnode(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	ft_create_line(char **line, t_list *stash)
{
	int	i;
	int	len;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			len++;
			i++;
		}
		stash = stash->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

void	ft_free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*(str++))
		len++;
	return (len);
}
