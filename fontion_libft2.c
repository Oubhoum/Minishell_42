/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fontion_libft2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 00:03:29 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/21 04:13:12 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alpha(char c)
{
	if (c != DQUOTES && c != SQUOTE && c != ' ' && c != '\t'
		&& c != '\r' && c != '\n' && c != '\v')
		return (1);
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ((void)0);
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ch;

	ch = (unsigned char *)s;
	while (*ch != (char)c)
	{
		if (*ch == '\0')
		{
			return (NULL);
		}
		ch++;
	}
	return ((char *)ch);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isalpha(int c)
{
	if (!(c >= 97 && c <= 122) && !(c >= 65 && c <= 90))
		return (0);
	return (1);
}
