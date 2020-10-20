/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <lmoulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 12:55:31 by jvaquer           #+#    #+#             */
/*   Updated: 2020/10/20 14:13:01 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void			set_read(t_reader *r)
{
	ft_memset(r->k, 0, 4);
	r->s = ft_calloc(2, sizeof(char));
	r->i = 0;
	r->len = 0;
	r->exit = 0;
	r->ent = 0;
}

void		free_histo(t_reader *r, t_historique *h)
{
	ft_free_av(h->tab);
//	ft_strdel(&r->s);
	ft_strdel(&h->tmp);
}
