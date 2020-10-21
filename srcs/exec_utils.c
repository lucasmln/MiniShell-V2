/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:17:22 by lucas             #+#    #+#             */
/*   Updated: 2020/10/21 15:04:41 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_get_path(t_exe *ex)
{
	int		pos;

	pos = ft_find_var_in_av(g_shell.env, "PATH=");
	if (pos == -1)
	{
		ex->error = 1;
		ex->path = ft_strdup("");
		return (0);
	}
	else
		ex->path = ft_strdup(&g_shell.env[pos][5]);
	return (1);
}

int			ft_pass_word(char *buf, int *i)
{
	int		check;

	if (!buf[*i])
		return (0);
	check = 0;
	while (buf[*i])
	{
		if (!check && buf[*i] == ' ')
		{
			ft_skip_space(buf, i);
			return (1);
		}
		else if (!check && (buf[*i] == '"' || buf[*i] == 39))
			check = buf[*i];
		else if (check && buf[*i] == check)
			check = 0;
		*i += 1;
	}
	return (1);
}

char		*ft_del_quote_av(char *s)
{
	int		len;
	char	*trim;
	char	*new;

	len = ft_len_without_quote(s);
	trim = ft_strtrim(s, " ");
	ft_strdel(&s);
	new = ft_copy_without_quote(trim, len);
	ft_strdel(&trim);
	return (new);
}

void		ft_incremente_pip_and_pid(t_exe *ex)
{
	g_shell.pip.i++;
	g_shell.pip.len++;
	g_shell.pid.i++;
	g_shell.pid.len++;
	ft_strdel(&ex->full_cmd);
}

void		ft_fill_argv(char **av, char *buf)
{
	int		i;
	int		start;
	int		l;
	char	c;

	i = 0;
	start = 0;
	l = 0;
	while (ft_pass_word(buf, &i))
	{
		c = buf[i];
		buf[i] = '\0';
		av[l++] = ft_strdup(&buf[start]);
		start = i;
		buf[i] = c;
	}
	av[l] = NULL;
}
