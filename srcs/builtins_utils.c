/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:49:34 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/13 11:49:45 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_change_env_pwd_utils(char *tmp, int i, char *path)
{
	int		pos;

	pos = ft_find_var_in_av(g_shell.sort_env, "PWD=");
	tmp = ft_str_add(ft_strdup("PWD="), ft_strdup(path));
	ft_strdel(&g_shell.env[i]);
	ft_strdel(&g_shell.sort_env[pos]);
	g_shell.sort_env[pos] = ft_strdup(tmp);
	g_shell.env[i] = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void		ft_change_env_pwd(char *path)
{
	int		pos;
	int		i;
	int		k;
	char	*tmp;

	pos = ft_find_var_in_av(g_shell.env, "OLDPWD=");
	i = ft_find_var_in_av(g_shell.env, "PWD=");
	k = ft_find_var_in_av(g_shell.sort_env, "OLDPWD=");
	if (pos == -1)
		ft_error_cd("OLDPWD", NO_PWD);
	if (i == -1)
		ft_error_cd("PWD", NO_PWD);
	if (i == -1 || pos == -1)
		return ;
	tmp = ft_str_add(ft_strdup("OLD"), ft_strdup(g_shell.env[i]));
	ft_strdel(&g_shell.env[pos]);
	ft_strdel(&g_shell.sort_env[k]);
	g_shell.sort_env[k] = ft_strdup(tmp);
	g_shell.env[pos] = ft_strdup(tmp);
	ft_strdel(&tmp);
	ft_change_env_pwd_utils(tmp, i, path);
	ft_strdel(&tmp);
	ft_strdel(&path);
}
