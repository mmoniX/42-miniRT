/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonika <mmonika@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 18:02:33 by mmonika           #+#    #+#             */
/*   Updated: 2025/04/22 15:35:34 by mmonika          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*concat;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	concat = (char *)malloc((ft_strlen(s1)
				+ ft_strlen(s2) + 1) * sizeof(char));
	if (!concat)
		return (free(s1), NULL);
	while (s1[i])
	{
		concat[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		concat[i + j] = s2[j];
		j++;
	}
	concat[i + j] = '\0';
	free(s1);
	return (concat);
}

char	*read_file(int fd, char *buffer)
{
	int		byte_read;
	char	*temp_buffer;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	temp_buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp_buffer)
		return (free (buffer), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(temp_buffer);
			free(buffer);
			return (NULL);
		}
		temp_buffer[byte_read] = '\0';
		buffer = get_strjoin(buffer, temp_buffer);
		if (ft_strchr(temp_buffer, '\n'))
			break ;
	}
	free(temp_buffer);
	return (buffer);
}

char	*read_line(char *buffer)
{
	char	*str;
	int		i;

	i = 0;
	if (!buffer || !*buffer)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		str = ft_calloc(i + 2, sizeof(char));
	else
		str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i] = '\n';
	return (str);
}

char	*update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free (buffer), NULL);
	i++;
	str = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!str)
		return (free(buffer), NULL);
	while (buffer[i])
	{
		str[j] = buffer[i];
		j++;
		i++;
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = read_line(buffer[fd]);
	if (!line)
	{
		free (buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}

// #include <stdio.h>
// int main(void)
// {
//     int fd = open("MrPotter.txt", O_RDONLY);
//     if (fd == -1)
//         return (-1);
// 	/*
// 	printf("Line1: %s\n", get_next_line(fd));
// 	printf("Line2: %s\n", get_next_line(fd));
// 	printf("Line3: %s\n", get_next_line(fd));
// 	printf("Line4: %s\n", get_next_line(fd));
// 	printf("Line5: %s\n", get_next_line(fd));
// 	*/
// 	char *output;
//     while ((output = get_next_line(fd)) != NULL)
//     {
//         printf("Line: %s\n", output);
//         free(output);
//     }
// 	close(fd);
//     return (0);
// }