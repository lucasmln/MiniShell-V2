/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 15:12:38 by lmoulin           #+#    #+#             */
/*   Updated: 2020/10/21 15:13:27 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_khome(t_reader *r, t_keys *keys)
{
	int		i;

	i = 0;
	while (i++ < r->i)
		write(1, keys->k_left, 3);
	r->i = 0;
	return (1);
}

int		ft_kend(t_reader *r, t_keys *keys)
{
	int		i;

	i = r->i;
	while (i++ < r->len)
		write(1, keys->k_right, 3);
	r->i = r->len;
	return (1);
}

int		ft_kenter(t_reader *r, t_historique *h)
{
	if (ft_strlen(r->s) > 0)
		ft_add_input(r, h);
	r->ent = 1;
	h->size++;
	h->i = -1;
	return (1);
}
