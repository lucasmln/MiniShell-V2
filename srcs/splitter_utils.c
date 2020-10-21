/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:02:52 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 15:02:54 by lmoulin          ###   ########.fr       */
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
