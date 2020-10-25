/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvaquer <jvaquer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:02:52 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/22 11:47:08 by jvaquer          ###   ########.fr       */
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

int			ft_check_str_redir(char *str)
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
			found = 1;
		else if (found && (str[i] > ' ' && str[i] < '~'))
			found = 0;
		else if (str[i] == 39)
			ft_go_to_char(str, &i, 39);
		else if (str[i] == '"')
			ft_go_to_char(str, &i, '"');
		else if (str[i] == '|' && found)
			break ;
		i++;
	}
	return (found);
}

int			ft_check_empty_redir(void)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_shell.semi_colon[i])
	{
		if (ft_check_str_redir(g_shell.semi_colon[i]))
		{
			ft_printf(1,
				"minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		i++;
	}
	return (0);
}
