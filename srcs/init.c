/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:50:22 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/08 18:31:18 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_init_fd_tab(void)
{
	int		i;

	i = 0;
	g_shell.out.fd[i] = 1;
	while (++i < FD_MAX)
		g_shell.out.fd[i] = -2;
	i = 0;
	g_shell.in.fd[i] = 1;
	while (++i < FD_MAX)
		g_shell.in.fd[i] = -2;
}

void		ft_copy_env_utils(const char **env, int i)
{
	char	*tmp;
	if (!(ft_strncmp(env[i], "SHLVL=", ft_strlen("SHLVL="))))
	{
		tmp = ft_itoa(ft_atoi(&env[i][ft_strlen("SHLVL=")]) + 1);
		g_shell.sort_env[i] = ft_str_add(ft_strdup("SHLVL="), tmp);
	}
	else
		g_shell.sort_env[i] = ft_strdup(env[i]);
}

void		ft_sort_env(void)
{
	int		i;
	char	*tmp;

	i = -1;
	while (g_shell.sort_env[++i + 1])
	{
		if (ft_strcmp(g_shell.sort_env[i], g_shell.sort_env[i + 1]) > 0)
		{
			tmp = g_shell.sort_env[i + 1];
			g_shell.sort_env[i + 1] = g_shell.sort_env[i];
			g_shell.sort_env[i] = tmp;
			i = i - 1 >= -1 ? -1 : i - 1;
		}
	}
}

int			ft_copy_env(const char **env)
{
	int		i;
	int		len;

	len = 0;
	while (env[len])
		len++;
	g_shell.len_env = len;
	g_shell.len_exp = len;
	if (!(g_shell.env = malloc(sizeof(char *) * (len + 1))) ||
					!(g_shell.sort_env = malloc(sizeof(char *) * (len + 1))))
		return (0);
	i = -1;
	while (env[++i])
		ft_copy_env_utils(env, i);
	g_shell.sort_env[i] = NULL;
	i = -1;
	while (g_shell.sort_env[++i])
		g_shell.env[i] = ft_strdup(g_shell.sort_env[i]);
	g_shell.env[i] = NULL;
	ft_sort_env();
	return (1);
}