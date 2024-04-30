/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crebelo- <crebelo-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:37:59 by crebelo-          #+#    #+#             */
/*   Updated: 2024/01/10 12:37:59 by crebelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "unistd.h"
#include <stdio.h>
#include <string.h>
// # define BUFFER_SIZE 10

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p;
	int				n;
	int				i;

	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	else
	{
		i = 0;
		n = nmemb * size;
		while (n-- > 0)
			p[i++] = '\0';
	}
	return (p);
}

int	ft_strlen(char *buffer)
{
	int	i;

	i = 0;
	if (buffer)
	{
		while(buffer[i] != '\0')
			i++;
	}
	return (i);
}

void update_buffer(int pos, char **buffer)
{
	int size;
	char *temp;
	int i;
	int j;

	i = 0;
	j = pos + 1;
	size = ft_strlen(*buffer);
	temp = (char *)ft_calloc(size - pos + 1, sizeof(char));
	if (!temp)
		return ;
	while (j < size)
		temp[i++] = (*buffer)[j++];
	free(*buffer);
	*buffer = temp;
}

char *get_line(int index, char *buffer)
{
	int i;
	char *line;

	i = 0;
	line = (char *)ft_calloc(index + 2, sizeof(char));
	while (i <= index) 
	{
		line[i] = buffer[i];
		i++;
	}
	return (line);
}

int get_bytes(int fd, char **buffer)
{
	int bytes;
	int size;
	int i;
	char *temp;
	char *line;

	if (*buffer)
		size = ft_strlen(*buffer);
	else
		size = 0;
	line = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!line)
		return (0);
	bytes = read(fd, line, BUFFER_SIZE);
	if (bytes)
	{
		temp = (char *)ft_calloc(size + bytes + 1, sizeof(char));
		if (!temp)
			return(0);
		i = 0;
		if (size)
		{
			while ((*buffer)[i])
			{
				temp[i] = (*buffer)[i];
				i++;
			}
		}
		size = 0;
		while (line[size])
		{
			temp[i] = line[size];
			i++;
			size++;
		}
		free(*buffer);
		free(line);
		*buffer = temp;
	}
	else
		free(line);
	return (bytes);
}

char *get_next_line(int fd)
{
	int			bytes;
	static char	*buffer = NULL;
	char		*line ;
	int			i;

	// if (fd <= 0 || BUFFER_SIZE <= 0)  //  For exam you can't check this!!
	// 	return (NULL);
	bytes = get_bytes(fd, &buffer);
	if (bytes == 0 && ft_strlen(buffer) == 0)
	{
		free(buffer);
		return (NULL);
	}
	while (bytes || buffer)
	{
		i = 0;
		while (i < ft_strlen(buffer) && buffer && buffer[i] != '\n')
			 i++;
		if (i > ft_strlen(buffer))
		{
			if (bytes != 0)
				bytes = get_bytes(fd, &buffer);
			else
				return (buffer);
		}
		else
		{
			line = get_line(i, buffer);
			update_buffer(i, &buffer);
			return (line);
		}
	}
	return (NULL);
}

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(void) {
	int fd = open("example2.txt", O_RDONLY);
	if (fd == -1) {
		perror("Failed to open file");
		return 1;
	}

	char *line;
	int		w;
	w = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{	break ;}
		printf("%s", line);
		free(line);
	}
	
	close(fd);
	return 0;
}