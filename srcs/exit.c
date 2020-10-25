/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 11:48:55 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/22 15:35:55 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_free_exit(void)
{
	ft_free_av(g_shell.pip_str);
	ft_free_av(g_shell.semi_colon);
	ft_free_av(g_shell.sort_env);
	ft_free_av(g_shell.env);
	ft_strdel(&g_shell.str);
	ft_strdel(&g_shell.dir);
	if (!(fill_history_a(g_shell.h, g_shell.r)))
		exit(1);
	exit(g_shell.ret);
}

int			ft_len_nb_successif(char *buf)
{
	int		len;
	int		i;

	len = 0;
	i = buf[0] == '-' ? 1 : 0;
	while (ft_isdigit(buf[len + i]))
		len++;
	return (len);
}

int			ft_too_high(char *buf)
{
	int		neg;

	neg = buf[0] == '-' ? 1 : 0;
	if (ft_len_nb_successif(&buf[neg]) < 18)
		return (0);
	if (ft_len_nb_successif(&buf[neg]) > 19)
		return (1);
	if (neg && ft_strncmp(&buf[neg], LLMAX, ft_strlen(&buf[neg])) > 0)
		return (1);
	if (!neg && ft_strncmp(&buf[neg], LLMIN, ft_strlen(&buf[neg])) > 0)
		return (1);
	return (0);
}

int			ft_check_exit_utils(char *buf, int i)
{
	int					nb;
	int					neg;

	neg = buf[i] == '-' ? 1 : 0;
	i = neg + i - 1;
	while (buf[++i])
	{
		nb = ft_isdigit(buf[i]) ? 1 : 0;
		if (buf[i] == ' ' && buf[i + 1] && buf[i + 1] != ' ')
		{
			ft_printf(1, "minishell: too many arguments\n");
			g_shell.legal_exit = 1;
			return ((g_shell.ret = 1) - 1);
		}
		if (!ft_isdigit(buf[i]) && buf[i] != ' ')
		{
			ft_printf(1, ARG_NUM, &buf[5]);
			return ((g_shell.ret = 2) - 1);
		}
	}
	if (nb)
		g_shell.ret = ft_atoll(&buf[5]);
	if (ft_too_high(&buf[5]))
		ft_printf(1, ARG_NUM, &buf[5]);
	return (1);
}

int			ft_check_exit(char *buf)
{
	int		i;
	int		nb;

	g_shell.legal_exit = 0;
	nb = 0;
	if ((!ft_strncmp(buf, "exit", 4) &&
				!buf[4]) || !ft_strncmp(buf, "exit ", 5))
	{
		i = 4;
		ft_skip_space(buf, &i);
		return (ft_check_exit_utils(buf, i));
	}
	return (0);
}
