/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:39:00 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/20 23:40:49 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && '9' >= c);
}

int	check_key_parssing(char *str)
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
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z'))
			&& !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static	void	free_node(t_environement *remove)
{
	free(remove->cle);
	free(remove->valeur);
	free(remove);
}

static	void	remove_node(t_environement **env, char *value)
{
	t_environement	*tmp_env;
	t_environement	*tmp;
	t_environement	*remov;

	tmp_env = *env;
	if (tmp_env && ft_strcmp(tmp_env->cle, value) == 0)
	{
		remov = tmp_env;
		tmp = tmp_env->next;
		free_node(remov);
		*env = tmp;
		return ;
	}
	while (tmp_env)
	{
		if ((tmp_env->next) && !(ft_strcmp(tmp_env->next->cle, value)))
		{
			remov = tmp_env->next;
			tmp = tmp_env->next->next;
			free_node(remov);
			tmp_env->next = tmp;
			return ;
		}
		tmp_env = tmp_env->next;
	}
}

void	ft_unsit(char **option, t_data *nv)
{
	t_environement	**tmp_env;
	int				i;

	tmp_env = &nv->environement;
	if (!tmp_env)
		return ;
	nv->exit_status = 0;
	i = 1;
	if (option && ft_strcmp(option[0], "unset") == 0)
	{
		while (option[i])
		{
			if (!check_key_parssing(option[i]))
				ft_perror("Invalide key", nv);
			else
				remove_node(tmp_env, option[i]);
			i++;
		}
	}
}
