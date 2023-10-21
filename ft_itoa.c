/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:43:48 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/13 00:00:54 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_num(long num)
{
	int	size;

	size = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num *= -1;
		size++;
	}
	while (num > 0)
	{
		num /= 10;
		size++;
	}
	return (size);
}

char	*ft_neg_num(long nb, char *s)
{
	if (nb < 0)
	{
		s[0] = '-';
		nb *= -1;
	}
	else if (nb == 0)
		s[0] = '0';
	return (s);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	long	nb;
	char	*str;

	nb = n;
	len = ft_size_num(nb);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	str[len] = '\0';
	if (nb <= 0)
	{
		ft_neg_num(nb, str);
		nb *= -1;
	}
	i = len - 1;
	while (nb > 0)
	{
		str[i] = (nb % 10) + 48;
		nb /= 10;
		i--;
	}
	return (str);
}
