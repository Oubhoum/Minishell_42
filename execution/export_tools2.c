/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:41:54 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/20 20:46:35 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_node(t_environement **env, char *s1, char *s2)
{
	t_environement	*tmp_env;
	t_environement	*tmp;

	tmp_env = malloc(sizeof(t_environement));
	if (!tmp_env)
		return ;
	tmp_env->cle = ft_strdup(s1);
	if (!s2)
		tmp_env->valeur = NULL;
	else
		tmp_env->valeur = ft_strdup(s2);
	tmp_env->next = NULL;
	if (!(*env))
	{
		*env = tmp_env;
		return ;
	}
	tmp = *env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = tmp_env;
}

size_t	get_value_len(char *str)
{
	size_t	index;

	index = get_ferst_equal_posetion(str);
	while (str[index])
		index++;
	return (index);
}

char	*get_key(char *str)
{
	size_t	index;

	index = get_ferst_equal_posetion(str);
	if (index > 0 && str[index - 1] && str[index - 1] == '+')
		return (ft_substr(str, 0, index - 1));
	else if (index != 0 && str[index - 1] && str[index - 1] != '+')
		return (ft_substr(str, 0, index));
	return (ft_strdup(str));
}

char	*get_value_ex(char *str)
{
	char	*value;
	size_t	start;
	size_t	len;

	start = get_ferst_equal_posetion(str);
	len = get_value_len(str);
	if (len == 0)
	{
		value = ft_strdup("");
		if (!value)
			return (NULL);
	}
	else
		value = ft_substr(str, (unsigned int)start + 1, len);
	return (value);
}
