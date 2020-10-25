/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 14:50:26 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/25 17:43:49 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_trim_spaces(char *var)
{
	char	*str;
	int		len;
	int		i;

	len = ft_len_without_space(var);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		exit(-1000);
	i = 0;
	len = 0;
	while (var[i])
	{
		str[len++] = var[i];
		if (var[i] == ' ')
			while (var[i] == ' ')
				i++;
		else
			i++;
	}
	str[len] = '\0';
	return (str);
}

char		ft_choose_good_quote(char *buf)
{
	int		i;

	i = 0;
	while (buf[i + 1])
	{
		if (buf[i] == 39)
			return ('"');
		else if (buf[i] == '"')
			return (39);
		i++;
	}
	return ('"');
}

int			ft_len_without_space(char *var)
{
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (var[i])
	{
		if (var[i] == ' ')
			while (var[i] == ' ')
				i++;
		else
			i++;
		len++;
	}
	return (len);
}

int			ft_init_redir(char *buf, int *i, int *check)
{
	g_shell.out.i = 0;
	g_shell.out.len = 0;
	g_shell.in.i = 0;
	g_shell.in.len = 0;
	if (ft_check_error_redir(buf))
	{
		ft_strdel(&buf);
		return (1);
	}
	*i = 0;
	*check = 0;
	return (0);
}

char		*ft_del_char(char *s, int pos)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!(new = malloc(sizeof(char) * (ft_strlen(s)))))
		exit(-1000);
	while (s[i])
	{
		if (i != pos)
			new[k++] = s[i++];
		if (i == pos)
			i++;
	}
	new[k] = '\0';
	return (new);
}