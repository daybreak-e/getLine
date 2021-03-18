/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saelee <saelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:46:42 by saelee            #+#    #+#             */
/*   Updated: 2021/03/18 18:32:22 by saelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_line(char **str, int n, char **line, int fd)
{
	char	*temp;
	int		i;

	i = 0;
	while (str[fd][i] && str[fd][i] != '\n')
		i++;
	*line = ft_substr(str[fd], 0, i);
	if (!str[fd][i])
	{
		temp = str[fd];
		str[fd] = NULL;
		free(temp);
		return (0);
	}
	else
	{
		temp = str[fd];
		str[fd] = ft_strdup((str[fd]) + i + 1);
		free(temp);
	}
	if (!str[fd] || !*line)
		return (-1);
	if (n || (n == 0 && str[fd] != NULL))
		return (1);
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	char			*buf;
	static char		*str[OPEN_MAX];
	char			*temp;
	int				n;

	buf = NULL;
	if (!line || fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0
			|| !(buf = malloc(BUFFER_SIZE + 1)) || read(fd, buf, 0) == -1)
		return (-1);
	if (!str[fd])
		if (!(str[fd] = ft_strdup("")))
			return (-1);
	while ((n = read(fd, buf, BUFFER_SIZE)))
	{
		temp = str[fd];
		buf[n] = '\0';
		if (!(str[fd] = ft_strjoin(str[fd], buf)))
			return (-1);
		free(temp);
		if (ft_strchr(str[fd], '\n') != NULL)
			break ;
	}
	free(buf);
	return (get_line(str, n, line, fd));
}
