/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_get_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:01:55 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 11:50:47 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		**ft_add_var_to_env(char *var, char **env)
{
	int		i;
	char	**new;

	if (!(new = malloc(sizeof(char *) * (ft_avlen(env) + 2))))
		exit(-1000);
	i = -1;
	while (env[++i])
		new[i] = ft_strdup(env[i]);
	new[i++] = ft_strdup(var);
	new[i] = NULL;
	return (new);
}

void		ft_replace_var_in_all_env(char *var, int check)
{
	int		pos[2];
	int		i;
	char	c;
	char	*tmp;

	i = 0;
	ft_go_to_char(var, &i, '=');
	c = var[i] ? var[++i] : var[i];
	var[i] = '\0';
	tmp = !c ? ft_str_add(ft_strdup(var), ft_strdup("=")) : ft_strdup(var);
	pos[0] = ft_find_var_in_av(g_shell.env, tmp);
	pos[1] = ft_find_var_in_av(g_shell.sort_env, tmp);
	var[i] = c;
	ft_strdel(&tmp);
	if (pos[0] != -1)
		ft_strdel(&g_shell.env[pos[0]]);
	if (pos[1] != -1)
		ft_strdel(&g_shell.sort_env[pos[1]]);
	if (pos[0] != -1)
		g_shell.env[pos[0]] = ft_strdup(var);
	if (pos[1] != -1)
		g_shell.sort_env[pos[1]] = ft_strdup(var);
}

void		ft_add_to_export(char **tmp, char *var)
{
	tmp = ft_add_var_to_env(var, g_shell.sort_env);
	ft_free_av(g_shell.sort_env);
	g_shell.sort_env = ft_avdup(tmp);
	ft_free_av(tmp);
}

int			ft_check_already_exist_var(char *var)
{
	int		pos[2];
	int		i;
	char	*test;
	char	*t;
	char	**tmp;

	t = ft_strdup(var);
	test = ft_get_pos_var(t, pos, &i);
	if (pos[1] != -1 && i)
		ft_replace_var_in_all_env(t, i);
	if (pos[0] == -1)
	{
		if (pos[0] == -1 && i)
		{
			tmp = ft_add_var_to_env(t, g_shell.env);
			ft_free_av(g_shell.env);
			g_shell.env = ft_avdup(tmp);
			ft_free_av(tmp);
		}
		if (pos[1] == -1)
			ft_add_to_export(tmp, t);
	}
	ft_strdel(&test);
	ft_strdel(&t);
	return (1);
}

char		*ft_get_pos_var(char *var, int pos[], int *i)
{
	int		k;
	char	c;
	char	*test;
	char	*tmp;

	k = 0;
	tmp = ft_strdup(var);
	ft_go_to_char(tmp, &k, '=');
	c = tmp[k];
	*i = c == '\0' ? 0 : 1;
	tmp[k] = '\0';
	test = ft_str_add(ft_strdup(tmp), ft_strdup("="));
	pos[0] = ft_find_var_in_av(g_shell.env, test);
	pos[1] = ft_find_var_in_av(g_shell.sort_env, test);
	tmp[k] = c;
	ft_strdel(&tmp);
	return (test);
}

char		*ft_change_var_utils(char *buf, char *new, int k, int check)
{
	if (check == -1)
		new[k++] = '"';
	new[k] = '\0';
	ft_strdel(&buf);
	return (new);
}

char		*ft_change_var(char *buf)
{
	char	*tmp_str;
	char	*new;
	int		i;
	char	k;
	int		check;

	tmp_str = ft_copy_without_quote(buf, ft_strlen(buf));
	if (!(new = malloc(sizeof(char) * (ft_strlen(tmp_str) + 1))))
		exit(-1000);
	i = -1;
	k = 0;
	check = 0;
	ft_go_to_char(tmp_str, &check, '=');
	while (tmp_str[++i])
	{
		new[k] = tmp_str[i];
		if (tmp_str[i] == '=' && check > 0 && tmp_str[check])
		{
			new[++k] = '"';
			check = -1;
		}
		k++;
	}
	ft_strdel(&tmp_str);
	return ((new = ft_change_var_utils(buf, new, k, check)));
}
