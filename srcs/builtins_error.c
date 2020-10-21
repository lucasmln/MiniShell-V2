/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:52:24 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 16:04:47 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_error_cd(char *buf, int type)
{
	char	*tmp;

	tmp = ft_get_word(buf, 0);
	if (type == NOT_FOUND)
		ft_printf(1, "minishell: %s: command not found\n", tmp);
	else if (type == NO_HOME)
		ft_printf(1, "minishell: cd: HOME not set\n");
	else if (type == NO_PWD)
		ft_printf(1, "minishell: cd: %s not set\n", buf);
	else if (type == NOT_DIR)
		ft_printf(1, "minishell: cd: %s: Not a directory\n", buf);
	ft_strdel(&tmp);
	return (0);
}

int			ft_check_wrong_char_unset(char *var)
{
	int		i;

	i = 0;
	while (var[i] == '"' || var[i] == 39)
		i++;
	if (!ft_isalpha(var[i]) && var[i] != '_')
		return (1);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_' &&
											var[i] != '"' && var[i] != 39)
			return (1);
		i++;
	}
	return (0);
}

int			ft_error_unset(char *buf)
{
	char	*tmp;

	tmp = ft_get_word(buf, 0);
	ft_printf(1, "minishell: %s: command not found\n", tmp);
	ft_strdel(&tmp);
	g_shell.tmp_ret = 127;
	return (1);
}

int			ft_check_error_unset(char *buf, int *start)
{
	int		i;
	char	check;

	i = 5;
	if (!buf[i] || buf[i] == ' ')
		return (0);
	if (buf[i] != '"' && buf[i] != 39)
		return (1);
	check = buf[i];
	while (buf[++i])
	{
		if (!check && buf[i] == ' ')
			break ;
		if (!check && (buf[i] == '"' || buf[i] == 39))
			check = buf[i++];
		if (buf[i] != check)
			return (1);
		if (check == buf[i])
			check = 0;
	}
	*start = i;
	return (0);
}