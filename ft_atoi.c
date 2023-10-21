/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:39:02 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/13 00:42:16 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_max_long(const char *str, long rev, int i, int sin)
{
	long	nb;

	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rev = nb;
		nb = (nb * 10) + str[i] - 48;
		if ((nb / 10) != rev)
		{
			if (sin == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	return (nb * sin);
}

int	ft_atoi(char *str)
{
	int		i;
	long	nb;
	int		sin;

	i = 0;
	sin = 1;
	nb = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sin *= -1;
		i++;
	}
	return (ft_max_long(str, nb, i, sin));
}

void	ft_free_str(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}
