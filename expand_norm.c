/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 23:54:00 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/13 18:46:46 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalphaa(int c)
{
	char	ch;

	ch = (char)c;
	return ((ch >= 'a' && ch <= 'z')
		|| (ch >= 'A' && ch <= 'Z'));
}

int	ft_isdigitt(int c)
{
	char	ch;

	ch = (char)c;
	return (ch >= '0' && ch <= '9');
}

int	ft_isalnum(int c)
{
	return (ft_isalphaa(c) || ft_isdigitt(c));
}

char	*getenvalue(char *name, char **env)
{
	int	namesize;
	int	i;

	if (!name)
		return (NULL);
	namesize = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(name, env[i], namesize) == 0
			&& env[i][namesize] == '=')
			return (env[i] + (namesize + 1));
		i++;
	}
	return (NULL);
}

void	init_expan_data(int *var_quot, char *line, int i)
{
	if (line[i] == '\"' && !var_quot[0])
		var_quot[1] = 1 - var_quot[1];
	else if (line[i] == '\'' && !var_quot[1])
		var_quot[0] = 1 - var_quot[0];
}
