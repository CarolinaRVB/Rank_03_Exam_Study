/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_short.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:07:45 by crebelo-          #+#    #+#             */
/*   Updated: 2024/01/15 12:07:45 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "unistd.h"
#include <stdio.h>
#include <fcntl.h>

void	ft_realloc(char **buffer, int index, int size)
{
	char	*temp;
	int		i;

	i = 0;
	temp = (char *)malloc(sizeof(char) * (size + index + 1));
	while(i < index)
	{
		temp[i] = (*buffer)[i];
		i++;
	}
	temp[i] = '\0';
	free(*buffer);
	*buffer = temp;
}

char    *get_next_line(int fd)
{
	char    *buffer;
	char    chr;
	int     bytes;
	int     index;

	bytes = read(fd, &chr, 1);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	index = 0;
	while (bytes)
	{
		buffer[index++] = chr;
		if (index > BUFFER_SIZE)
		{
			ft_realloc(&buffer, index, BUFFER_SIZE);
			if (!buffer)
				return (NULL);
		}
		if (chr == '\n')
			break ;
		bytes = read(fd, &chr, 1);
	}
	if (bytes == 0 && index == 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[index] = '\0';
	return (buffer);
}


// int	main()
// {
// 	int fd;
// 	char    *line;

// 	fd = open("example2.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (!line)
// 			return (0);
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// }