/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmoulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:26:29 by lmoulin           #+#    #+#             */
/*   Updated: 2019/10/25 18:49:22 by lmoulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned long long		ft_atoll(const char *str)
{
	long				i;
	int					negative;
	unsigned long long			nb;

	i = 0;
	negative = 1;
	nb = 0;
	while ((str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ') && str[i])
		i++;
	if (str[i] == '-')
	{
		negative = -negative;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (str[i] - '0') + nb * 10;
		i++;
	}
	return (nb * negative);
}
