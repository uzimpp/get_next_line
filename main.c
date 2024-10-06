/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:46:24 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/06 16:46:27 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*str;
	int		i;

	fd = open("./tb", O_RDONLY);
	i = 1;
	str = get_next_line(fd);
	printf("Time %d: %s", i, str);
	i++;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("Time %d: %s", i, str);
		free(str);
		i++;
	}
	close(fd);
	return (0);
}
