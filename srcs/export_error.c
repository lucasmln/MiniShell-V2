/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:57:35 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/26 14:47:39 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_error_export(char *buf, int type)
{
	char	*tmp;

	tmp = ft_get_word(buf, 0);
	if (type == NOT_FOUND)
		ft_printf(1, "minishell: %s: command not found\n", tmp);
	ft_strdel(&tmp);
	close(g_shell.pip.id[g_shell.pip.i][1]);
	g_shell.tmp_ret = 127;
	g_shell.pip.i++;
	g_shell.pip.len++;
	return (0);
}

int			ft_check_error_export(char *buf)
{
	int		i;
	int		cmp;
	int		check;

	i = 6;
	check = buf[i];
	cmp = 1;
	g_shell.tmp_ret = !g_shell.pip_str[g_shell.i_p + 1] ? 0 : g_shell.tmp_ret;
	if (buf[i] == '"' || buf[i] == 39)
	{
		while (check)
		{
			i++;
			if (check && buf[i] == check)
				check = 0;
			if (check && buf[i] != check)
				check = 0;
			if (!check && (buf[i] == '"' || buf[i] == 39))
				check = buf[i];
			cmp++;
		}
	}
	else if (buf[i] != '\0' && buf[i] != ' ')
		return (NOT_FOUND);
	return (cmp % 2 == 0 ? NOT_FOUND : 0);
}

int			ft_check_wrong_char(char *var)
{
	int		i;

	i = 0;
	while (var[i] == '"' || var[i] == 39)
		i++;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (1);
	while (var[i])
	{
		if (var[i] == '=')
			return (0);
		if (!ft_isalnum(var[i]) && var[i] != '_' &&
												var[i] != '"' && var[i] != 39)
			return (1);
		i++;
	}
	return (0);
}

int			ft_check_error_redir(char *buf)
{
	int		i;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '>' || buf[i] == '<')
		{
			i++;
			if (buf[i] && buf[i] == '>')
				i++;
			ft_skip_space(buf, &i);
			if (buf[i] == '\0' || buf[i] == '<' || buf[i] == '>')
			{
				ft_printf(1, "minishell: syntax error near unexpected token\n");
				return ((g_shell.ret = 258));
			}
		}
	}
	return (0);
}

int			ft_error_open_fd(char *buf)
{
	ft_strdel(&buf);
	return ((g_shell.ret = 1));
}
