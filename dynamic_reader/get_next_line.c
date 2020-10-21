/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:24:16 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 11:13:58 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_realloc(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		k;

	if (!(new = malloc(sizeof(char) * (ft_strlen2(s1) + ft_strlen2(s2) + 1))))
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			new[i] = s1[i];
			i++;
		}
	}
	k = 0;
	if (s2)
		while (s2[k])
			new[i++] = s2[k++];
	new[i] = '\0';
	ft_strdel(&s1);
	return (new);
}

int		get_char(int fd, char **line, char *buf)
{
	int		ret;

	ret = read(fd, buf, BUFFER_SIZE - BUFFER_SIZE + 1);
	if (ret == 0)
		return (0);
	if (buf[0] == '\n')
		return (1);
	buf[1] = '\0';
	*line = ft_realloc(*line, buf);
	return (2);
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		buf[BUFFER_SIZE - BUFFER_SIZE + 2];

	if (fd < 0 || !line || BUFFER_SIZE < 1 ||
		!(*line = malloc(sizeof(char) * 1)))
		return (-1);
	*line[0] = '\0';
	if ((ret = read(fd, buf, BUFFER_SIZE - BUFFER_SIZE + 1)) < 0)
		return (-1);
	if (ret == 0)
		return (0);
	buf[1] = '\0';
	if (buf[0] == '\n')
		return (1);
	*line = ft_realloc(*line, buf);
	while ((ret = get_char(fd, line, buf)) == 2)
		;
	return (ret);
}
