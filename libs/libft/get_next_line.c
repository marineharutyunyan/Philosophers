/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maharuty <maharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:34:00 by maharuty          #+#    #+#             */
/*   Updated: 2022/10/29 12:09:19 by maharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_line(int fd, char *old_buff)
{
	char	*buff;
	int		read_;

	read_ = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (read_ != 0 && !ft_strchr_gnl(old_buff, '\n'))
	{
		read_ = read(fd, buff, BUFFER_SIZE);
		if (read_ == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_] = '\0';
		old_buff = ft_strjoin_gnl(old_buff, buff);
	}
	free(buff);
	return (old_buff);
}

char	*before(char *buffer)
{
	size_t	i;
	char	*befor_string;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	befor_string = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		befor_string[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		befor_string[i] = buffer[i];
		i++;
	}
	befor_string[i] = '\0';
	return (befor_string);
}

char	*after(char *buffer)
{
	char	*after;
	size_t	i;
	size_t	c;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	after = (char *)malloc(sizeof(char) * (ft_strlen_gnl(buffer) - i + 1));
	i++;
	c = 0;
	while (buffer[i])
		after[c++] = buffer[i++];
	after[c] = '\0';
	free(buffer);
	return (after);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	line = before(buffer);
	buffer = after(buffer);
	return (line);
}
