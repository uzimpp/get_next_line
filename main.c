/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkullana <wkullana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:46:24 by wkullana          #+#    #+#             */
/*   Updated: 2024/10/17 07:43:47 by wkullana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
// https://github.com/uzimpp/get_next_line

// ==== Mandatory ====
// cc -Wall -Wextra -Werror $(ls *.c *.h | grep -v '_bonus') -D BUFFER_SIZE=1
#include "get_next_line.h"

// ==== Bonus ====
// cc -Wall -Wextra -Werror *_bonus.c *_bonus.h main.c -D BUFFER_SIZE=1
// #include "get_next_line_bonus.h"

#ifndef NUM_FILES
# define NUM_FILES 3
#endif

void	test_mandatory(void)
{
	int		fd;
	char	*str;
	int		i;
	int		line;

	fd = open("./get_next_line.c", O_RDONLY);
	i = 1;
	line = 1;
	while (1)
	{
		str = get_next_line(fd);
		printf("file %d, line %d: %s", i, line++, str);
		if (!str)
			break ;
		free(str);
	}
	close(fd);
}

void	print_bonus(int *fds, int *ended)
{
	int		i;
	int		line;
	char	*str;

	i = 0;
	line = 1;
	while (!(ended[0] && ended[1] && ended[2]))
	{
		i = 0;
		while (i < NUM_FILES)
		{
			str = get_next_line(fds[i]);
			if (str)
			{
				printf("file %d, line %d: %s", 1 + i++, line, str);
				free(str);
			}
			else
			{
				printf("file %d, line %d: %s\n", 1 + i, line, str);
				ended[i++] = 1;
			}
		}
		line++;
	}
}

void	test_bonus(void)
{
	int		i;
	int		fds[NUM_FILES];
	int		ended[NUM_FILES];

	fds[0] = open("tests/test1.txt", O_RDONLY);
	fds[1] = open("tests/test2.txt", O_RDONLY);
	fds[2] = open("tests/test3.txt", O_RDONLY);
	i = 0;
	while (i < NUM_FILES)
		ended[i++] = 0;
	print_bonus(fds, ended);
	i = 0;
	while (i < NUM_FILES)
		close(fds[i++]);
}

int	main(void)
{
	test_mandatory();
	// test_bonus();
	return (0);
}
