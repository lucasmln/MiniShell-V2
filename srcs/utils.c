/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:43:00 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/14 19:12:17 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_str_add(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		k;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 || !s2)
	{
		new = !s2 ? ft_strdup(s1) : ft_strdup(s1);
		!s2 ? ft_strdel(&s1) : ft_strdel(&s2);
		return (new);
	}
	if (!(new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		exit(-1000);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	k = -1;
	while (s2[++k])
	{
		new[i + k] = s2[k];
	}
	new[i + k] = '\0';
	ft_strdel(&s1);
	ft_strdel(&s2);
	s1 = NULL;
	s2 = NULL;
	return (new);
}

int			ft_go_to_char(char *s, int *i, char c)
{
	while (s[*i])
	{
		if (s[*i] == c)
			return (1);
		*i += 1;
	}
	return (0);
}

char		*ft_get_word(char *buf, char stopper)
{
	int		i;
	int		len;
	int		save;

	i = 0;
	len = 0;
	g_shell.check = 0;
	ft_skip_space(buf, &i);
	save = i;
	while (buf[i + len])
	{
		if (g_shell.check == 0 && ((!buf[i + len] || buf[i + len] == ' ') || buf[i + len] == stopper))
			break ;
		if ((buf[i + len] == 39 || buf[i + len] == '"') && g_shell.check == 0)
			g_shell.check = buf[i++ + len];
		else if (g_shell.check == buf[i + len])
		{
			g_shell.check = 0;
			i++;
		}
		else
			len++;
	}
	return (ft_copy_without_quote(&buf[save], len));
}

int			ft_find_var_in_av(char **av, char *str)
{
	int		i;
	int		k;
	char	c;
	char	*tmp;

	i = -1;
	while (av[++i])
	{
		k = 0;
		c = 0;
		ft_go_to_char(av[i], &k, '=');
		c = av[i][k] == '=' ? av[i][k] : av[i][k];
		av[i][k] = '\0';
		tmp = ft_str_add(ft_strdup(av[i]), ft_strdup("="));
		if (!ft_strncmp(tmp, str, ft_strlen(str)))
		{
			ft_strdel(&tmp);
			av[i][k] = c;
			return (i);
		}
		ft_strdel(&tmp);
		av[i][k] = c;
	}
	return (-1);
}

int			ft_error_open_fd(char *buf)
{
	ft_strdel(&buf);
	return ((g_shell.ret = 1));
}
