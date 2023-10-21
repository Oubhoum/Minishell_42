/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 21:17:15 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/10 21:21:22 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_equal_or_plus(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ftt_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

size_t	get_ferst_equal_posetion(char	*str)
{
	size_t	posetion;

	posetion = 0;
	if (!str)
		return (0);
	while (str[posetion])
	{
		if (str[posetion] == '=')
			return (posetion);
		posetion++;
	}
	return (0);
}
