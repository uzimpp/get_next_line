/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:58:36 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/06 16:12:53 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
void	readstash( int fd, t_list **stash);
void	ft_append(t_list **stash, char *buff, int status);
void	clean_stash(t_list **stash);
void	extract_line(t_list *stash, char **line);

int		ft_isnotnewline(t_list *stash);
t_list	*ft_getlastnode(t_list *stash);
void	ft_create_line(char **line, t_list *stash);
void	ft_free_stash(t_list *stash);
int		ft_strlen(char *str);

#endif