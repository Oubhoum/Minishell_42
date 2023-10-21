/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expoet_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 15:49:21 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/13 18:21:33 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_append(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z')) && str[0] != '_')
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_append(t_environement **env, char *cle, char *valeur)
{
	t_environement	*tmp_env;
	char			*tmp;

	tmp_env = *env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->cle, cle) == 0)
		{
			tmp = tmp_env->valeur;
			tmp_env->valeur = ft_strjoin(tmp, valeur);
			free(tmp);
		}
		tmp_env = tmp_env->next;
	}
}

char	*get_key_append(char *str)
{
	int		index;

	index = 1;
	if (!str)
		return (NULL);
	while (str[index])
	{
		if (str[index] == '+' && str[index + 1] == '=')
			return (ft_substr(str, 0, index));
		index++;
	}
	return (ft_substr(str, 0, ft_strlen(str)));
}

char	*get_value_append(char *str)
{
	int		index;
	int		i;
	int		j;
	char	*value;

	index = 1;
	i = 0;
	j = 0;
	while (str[index])
	{
		if ((str[index] == '+' && str[index + 1] == '=') || (str[i] == '='))
		{
			i = index;
			j = index + 1;
			break ;
		}
		index++;
	}
	value = ft_substr(str, j + 1, ft_strlen(str) - i);
	if (!value)
		return (NULL);
	return (value);
}
