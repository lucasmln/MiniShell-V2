/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:45:04 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/08 18:31:25 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ft_set_parse(char *buf)
{
	char		*tmp;
	int			i;

	ft_init_fd_tab();
	if (!g_shell.semi_colon[g_shell.i_s + 1])
		if (buf[ft_strlen(buf) - 1] == '\n')
			buf[ft_strlen(buf) - 1] = '\0';
	ft_split_pipe(buf);
	if (g_shell.error == -1)
	{
		ft_free_error(ERR_PIPE);
		return (0);	
	}
	ft_check_env_var();
	g_shell.i_p = -1;
	while (g_shell.pip_str[++g_shell.i_p])
	{
		tmp = ft_strdup(g_shell.pip_str[g_shell.i_p]);
		ft_get_cmd(tmp);
		ft_strdel(&g_shell.pip_str[g_shell.i_p]);
		ft_close_fd();
	}
	ft_strdel_av(&g_shell.pip_str);
	return (1);
}

void		ft_split_pipe(char *buf)
{
	int		len;

	len = ft_len_split(buf, '|');
	if (!(g_shell.pip_str = malloc(sizeof(char *) * (len + 1))))
		exit(-1000);
	ft_printf(1, "len = %d\n", len);
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
	char	quote;
	int		save;
	int		k;

	i = 0;
	quote = 0;
	k = 0;
	save = 0;
	while (buf[i])
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
			if (buf[i] == splitter)
				g_shell.error = -1;
			save = i;
		}
		i++;
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
	while (g_shell.semi_colon[++g_shell.i_s])
	{
		if (!ft_set_parse(g_shell.semi_colon[g_shell.i_s]))
			return (0);
	//	ft_free_av(g_shell.pip_str);
		i = -1;
	}
	return (1);
}
