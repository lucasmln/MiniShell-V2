/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:45:04 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/15 18:54:31 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_init_set_parse(char *buf, int *ret)
{
	if (!buf[0])
		return (1);
	ft_check_env_var();
	g_shell.i_p = -1;
	g_shell.last_pip = 0;
	*ret = -1000;
	return (0);
}

int			ft_set_parse(char *buf)
{
	char		*tmp;
	int			ret;
	int			i;

	ft_init_fd_tab();
	if (!g_shell.semi_colon[g_shell.i_s + 1])
		if (buf[ft_strlen(buf) - 1] == '\n')
			buf[ft_strlen(buf) - 1] = '\0';
	ft_split_pipe(buf);
	if (g_shell.error == -1)
		return (ft_free_error(ERR_PIPE));
	if (ft_init_set_parse(buf, &ret))
		return (0);
	while (g_shell.pip_str[++g_shell.i_p])
	{
		g_shell.error_input = 0;
		tmp = ft_strdup(g_shell.pip_str[g_shell.i_p]);
		ret == -1000 ? (ret = ft_try_cmd(tmp)) : ft_try_cmd(tmp);
		ft_strdel(&g_shell.pip_str[g_shell.i_p]);
		ft_close_fd();
	}
	ft_strdel_av(&g_shell.pip_str);
	ft_final_exec(ret);
	return (1);
}

void		ft_split_pipe(char *buf)
{
	int		len;

	len = ft_len_split(buf, '|');
	if (!(g_shell.pip_str = malloc(sizeof(char *) * (len + 1))))
		exit(-1000);
	ft_add_split(buf, g_shell.pip_str, '|');
}

int			ft_len_split(char *buf, char splitter)
{
	int		i;
	int		len;
	int		quote;

	i = 0;
	len = 1;
	quote = 0;
	while (buf[i])
	{
		if ((buf[i] == 39 || buf[i] == '"') && quote == 0)
			quote = buf[i];
		else if (buf[i] == quote)
			quote = 0;
		else if (buf[i] == splitter && quote == 0)
			len++;
		i++;
	}
	return (len);
}

void		ft_add_split(char *buf, char **av, char splitter)
{
	int		i;
	int		quote;
	int		save;
	int		k;

	ft_init_var(&i, &quote, &save, &k);
	i = -1;
	while (buf[++i])
	{
		if ((buf[i] == 39 || buf[i] == '"') && quote == 0)
			quote = buf[i];
		else if (buf[i] == quote)
			quote = 0;
		else if (buf[i] == splitter && quote == 0)
		{
			buf[i] = '\0';
			av[k++] = ft_strdup(&buf[save]);
			buf[i++] = splitter;
			ft_skip_space(buf, &i);
			g_shell.error = buf[i] == splitter ? -1 : g_shell.error;
			save = i;
		}
	}
	av[k++] = ft_strdup(&buf[save]);
	av[k] = NULL;
}

void		ft_split_semi_colons(char *buf)
{
	int		len;

	len = 0;
	len = ft_len_split(buf, ';');
	if (!(g_shell.semi_colon = malloc(sizeof(char *) * (len + 1))))
		exit(-1000);
	ft_add_split(buf, g_shell.semi_colon, ';');
	g_shell.i_p = 0;
}

int			ft_check_parse(char *buf)
{
	int		i;

	g_shell.i_s = -1;
	g_shell.tmp_ret = -100000;
	while (g_shell.semi_colon[++g_shell.i_s])
	{
		g_shell.pip.i = 0;
		g_shell.pip.len = 0;
		g_shell.pid.i = 0;
		g_shell.pid.len = 0;
		g_shell.pos_error_in = -1;
		if (!ft_set_parse(g_shell.semi_colon[g_shell.i_s]))
			return (0);
		i = -1;
	}
	return (1);
}
