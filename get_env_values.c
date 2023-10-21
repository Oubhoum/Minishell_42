/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:58:27 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/13 00:40:21 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	linked_list_len(t_environement *env)
{
	t_environement		*tmp_env;
	int					len;

	tmp_env = env;
	len = 0;
	while (tmp_env)
	{
		tmp_env = tmp_env->next;
		len++;
	}
	return (len + 1);
}

char	**get_env_values_table(t_environement *env)
{
	t_environement	*tmp_env;
	int				i;
	char			**str;
	char			*str1;

	i = 0;
	tmp_env = env;
	str = (char **)malloc(linked_list_len(env) * sizeof(char *));
	if (!str)
		return (NULL);
	tmp_env = env;
	while (tmp_env)
	{
		str1 = ft_strjoin("=", tmp_env->valeur);
		str[i] = ft_strjoin(tmp_env->cle, str1);
		free(str1);
		tmp_env = tmp_env->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	free_2d_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
