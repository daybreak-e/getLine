/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saelee <saelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:47:09 by saelee            #+#    #+#             */
/*   Updated: 2021/03/18 18:28:52 by saelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int				get_line(char **bon, int n, char **line, int fd)
{
	char		*temp;
	int			i;

	i = 0;
	while (bon[fd][i] && bon[fd][i] != '\n')
		i++;
	*line = ft_substr(bon[fd], 0, i);
	if (!bon[fd][i])
	{
		temp = bon[fd];
		bon[fd] = NULL;
		free(temp);
		return (0);
	}
	else
	{
		temp = bon[fd];
		bon[fd] = ft_strdup((bon[fd]) + i + 1);
		free(temp);
	}
	if (!bon[fd] || !*line)
		return (-1);
	if (n || (n == 0 && bon[fd] != NULL))
		return (1);
	return (-1);
}

int				get_next_line(int fd, char **line)
{
	char				*buf;
	static char			*bon[OPEN_MAX];
	char				*temp;
	int					n;

	buf = NULL;
	if (!line || fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0
			|| !(buf = malloc(BUFFER_SIZE + 1)) || read(fd, buf, 0) == -1)
		return (-1);
	if (!bon[fd])
		if (!(bon[fd] = ft_strdup("")))
			return (-1);
	while ((n = read(fd, buf, BUFFER_SIZE)))
	{
		temp = bon[fd];
		buf[n] = '\0';
		if (!(bon[fd] = ft_strjoin(bon[fd], buf)))
			return (-1);
		free(temp);
		if (ft_strchr(bon[fd], '\n') != 0)
			break ;
	}
	free(buf);
	return (get_line(bon, n, line, fd));
}
