/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:46:24 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/09 02:23:03 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
// https://github.com/uzimpp/get_next_line

// ==== Mandatory ====
// cc -Wall -Wextra -Werror $(ls *.c *.h | grep -v '_bonus')
// #include "get_next_line.h"

// ==== Bonus ====
// cc -Wall -Wextra -Werror *_bonus.c *_bonus.h main.c
#include "get_next_line_bonus.h"

#define NUM_FILES 3

void	test_mandatory(void)
{
	int		fd;
	char	*str;
	int		i;
	int		line;

	fd = open("./test.txt", O_RDONLY);
	i = 1;
	line = 1;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		printf("file %d, line %d: %s", i++, line++, str);
		free(str);
	}
	close(fd);
}

void	test_bonus(void)
{
	int		ended[3];
	char	*str;
	int		fds[3];
	int		line;
	int		i;

	fds[0] = open("tests/test1.txt", O_RDONLY);
	fds[1] = open("tests/test2.txt", O_RDONLY);
	fds[2] = open("tests/test3.txt", O_RDONLY);
	line = 1;
	for (i = 0; i < 3; i++)
		ended[i] = 0;
	while (!(ended[0] && ended[1] && ended[2]))
	{
		for (i = 0; i < 3; i++)
		{
			str = get_next_line(fds[i]);
			if (str)
			{
				printf("file %d, line %d: %s", i + 1, line++, str);
				free(str);
			}
			else
			{
				printf("file %d, line %d: %s\n", i + 1, line++, str);
				ended[i] = 1;
			}
		}
	}
	for (i = 0; i < 3; i++)
		close(fds[i]);
}

int	main(void)
{
	// test_mandatory();
	test_bonus();
	return (0);
}
