/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopaning <jopaning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 15:16:42 by jopaning          #+#    #+#             */
/*   Updated: 2020/03/12 16:12:27 by jopaning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr(const char *p, int c)
{
	char	*temp;

	temp = (char *)p;
	while (*temp)
	{
		if (*temp == c)
			return (temp);
		temp++;
	}
	if (*temp == '\0' && c == '\0')
		return (temp);
	return (0);
}

char		*ft_strnew(size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		str[i] = '\0';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	ft_new_line(char **s, char **line, int fd, int ret)
{
	char	*temp;
	int		len;

	len = 0;
	while (s[fd][len] != '\n' && s[fd][len] != '\0')
		len++;
	if (s[fd][len] == '\n')
	{
		if (!(*line = ft_substr(s[fd], 0, len)))
			return (-1);
		if (!(temp = ft_strdup(s[fd] + len + 1)))
			return (-1);
		free(s[fd]);
		s[fd] = temp;
		(s[fd][0] == '\0') ? ft_strdel(&s[fd]) : 0;
	}
	else if (s[fd][len] == '\0')
	{
		if (ret == BUFFER_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
		return (0);
	}
	return (1);
}

int			ft_malloc(char **line)
{
	if (!(*line = malloc(sizeof(char))))
		return(-1);
	(*line)[0] = 0;
	return(0);
}

int			get_next_line(int fd, char **line)
{
	int			verif;
	char		buffer[BUFFER_SIZE + 1];
	char		*temp;
	static char	*str[4096];

	if (fd < 0 || line == 0)
		return (-1);
	while ((verif = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[verif] = '\0';
		(str[fd] == NULL) ? str[fd] = ft_strnew(1) : str[fd];
		temp = ft_strjoin(str[fd], buffer);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (verif < 0)
		return (-1);
	if (verif == 0 && (str[fd] == 0 || str[fd][0] == '\0'))
		return (ft_malloc(line));
	return (ft_new_line(str, line, fd, verif));
}
