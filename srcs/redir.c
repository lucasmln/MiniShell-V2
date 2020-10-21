/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:01:39 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 15:07:33 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_redir_output(char *buf, int *i, int type)
{
	int		save;
	char	c;
	char	*name;
	char	rd[BUF_SIZE];

	*i += 1;
	*i = type ? *i + 1 : *i;
	name = ft_find_good_name_redir(buf, i);
	if (type)
	{
		g_shell.out.fd[g_shell.out.i] = open(name, O_CREAT |
				O_RDWR, S_IRUSR | S_IROTH | S_IRGRP | S_IWUSR, 0640);
		while (read(g_shell.out.fd[g_shell.out.i], rd, BUF_SIZE))
			;
	}
	else
		g_shell.out.fd[g_shell.out.i] = open(name, O_TRUNC | O_CREAT |
				O_RDWR, S_IRUSR | S_IROTH | S_IRGRP | S_IWUSR, 0640);
	ft_strdel(&name);
	if (g_shell.out.fd[g_shell.out.i] < 0)
		return (0);
	g_shell.out.i++;
	g_shell.out.len++;
	return (1);
}

char		*ft_find_good_name_redir(char *buf, int *i)
{
	char	*name;
	char	*tmp;
	int		save;

	save = *i;
	name = ft_get_word(&buf[*i], '>');
	*i = save;
	tmp = ft_get_word(&buf[*i], '<');
	if (ft_strlen(tmp) < ft_strlen(name))
	{
		ft_strdel(&name);
		return (tmp);
	}
	ft_strdel(&name);
	ft_strdel(&tmp);
	*i = save;
	return (ft_get_word(&buf[*i], '>'));
}

int			ft_redir_input(char *buf, int *i)
{
	int		save;
	char	*name;
	char	*tmp;
	char	c;

	*i += 1;
	save = *i;
	name = ft_find_good_name_redir(buf, i);
	g_shell.in.fd[g_shell.in.i] = open(name, O_RDONLY);
	if (g_shell.in.fd[g_shell.in.i] < 0)
	{
		g_shell.error_input = 1;
		g_shell.pos_error_in = g_shell.i_p;
		ft_printf(1, "minishell: %s: No such file or directory\n", name);
		ft_strdel(&name);
		return (1);
	}
	ft_strdel(&name);
	g_shell.in.i++;
	g_shell.in.len++;
	return (1);
}

int			ft_cond_chekc_redir(char *buf, int *i, int check)
{
	if (!check && buf[*i] == '>')
	{
		if (!ft_redir_output(buf, i, buf[*i + 1] != '>' ? 0 : 1))
			return (0);
	}
	else if (!check && buf[*i] == '<')
	{
		if (!ft_redir_input(buf, i))
			return (0);
	}
	return (1);
}

int			ft_check_redir(char *buf)
{
	int		i;
	int		check;

	if (ft_init_redir(buf, &i, &check))
		return (1);
	while (buf[i])
	{
		if (!check && (buf[i] == '"' || buf[i] == 39))
			check = buf[i++];
		else if (check == buf[i])
		{
			check = 0;
			i++;
		}
		else if (!check && (buf[i] == '>' || buf[i] == '<'))
		{
			if (!ft_cond_chekc_redir(buf, &i, check))
				return (ft_error_open_fd(buf));
		}
		else
			i++;
	}
	return (0);
}
