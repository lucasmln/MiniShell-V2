/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:26:35 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/20 12:19:12 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen2(const char *s)
{
	size_t len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}
