/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 14:58:02 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/22 17:55:00 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char		*ft_copy_without_quote(char *buf, int len)
{
	char	*word;
	int		i;
	int		k;

	g_shell.check = 0;
	if (!(word = malloc(sizeof(char) * (len + 1))))
		exit(-1000);
	i = 0;
	k = 0;
	while (buf[i])
	{
		if (!g_shell.check && (buf[i] == 39 || buf[i] == '"'))
			g_shell.check = buf[i++];
		else if (g_shell.check == buf[i])
		{
			g_shell.check = 0;
			i++;
		}
		else if (k == len)
			break ;
		else
			word[k++] = buf[i++];
	}
	word[k] = '\0';
	return (word);
}

int			ft_len_without_quote(char *buf)
{
	int		i;
	int		len;
	int		check;

	check = 0;
	len = 0;
	i = 0;
	while (buf[i])
	{
		if (check == 0 && (buf[i] == '"' || buf[i] == 39))
			check = buf[i++];
		else if (check == buf[i])
		{
			check = 0;
			i++;
		}
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}
