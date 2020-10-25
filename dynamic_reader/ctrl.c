/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 16:29:51 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/22 17:37:32 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			ctrl(t_reader *r)
{
	int		save;

	r->ent = 1;
	save = g_shell.ret;
	write(1, "\n", 1);
	if (r->c == 3)
		r->s = ft_strdup("\n");
	else if (r->c == 12)
		r->s = ft_strdup("clear\n");
	return (0);
}

int			ctrl_kdel(t_keys *keys, t_reader *r)
{
	if (r->i < r->len)
	{
		r->i++;
		write(1, keys->k_right, 3);
		ft_kdel(keys, r);
	}
	return (1);
}
