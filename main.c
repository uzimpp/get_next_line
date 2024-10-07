/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:46:24 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/07 12:08:46 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line_bonus.h"
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*str;
	int		i;

	fd = open("./test", O_RDONLY);
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
