/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remlissage2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:08:56 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/17 13:13:14 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_is_empty(t_environement **env_list)
{
	add_env(env_list, creat_env(ft_strdup("PATH"), ft_strdup(_PATH_STDPATH)));
	add_env(env_list, creat_env(ft_strdup("PWD"), getcwd(NULL, 0)));
	add_env(env_list, creat_env(ft_strdup("SHLVL"), ft_strdup("1")));
	add_env(env_list, creat_env(ft_strdup("_"), ft_strdup("/usr/bin/env")));
}

static	void	updat_value_shl(t_environement **env, char *cle, char *valeur)
{
	t_environement	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->cle, cle) == 0)
		{
			if (tmp_env->valeur)
				free(tmp_env->valeur);
			tmp_env->valeur = valeur;
			break ;
		}
		tmp_env = tmp_env->next;
	}
}

static	int	shell_level(t_environement *tmp)
{
	int	sh_lvl;

	sh_lvl = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "SHLVL"))
		{
			if (ft_atoi(tmp->valeur) < 0)
				sh_lvl = 0;
			else if (ft_atoi(tmp->valeur) > 999)
			{
				ft_putstr_fd("minishell: warning: shell level\
					(1001) too high, resetting to 1\n", 2);
				sh_lvl = 1;
			}
			else
				sh_lvl = ft_atoi(tmp->valeur) + 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (sh_lvl);
}

void	add_variables(t_environement **env_list)
{
	t_environement	*tmp;

	tmp = *env_list;
	if (if_key_exist(*env_list, "OLDPWD"))
		add_env(env_list, creat_env(ft_strdup("OLDPWD"), NULL));
	if (if_key_exist(*env_list, "PATH"))
		add_env(env_list, creat_env(ft_strdup("PATH"),
				ft_strdup(_PATH_STDPATH)));
	if (if_key_exist(*env_list, "SHLVL"))
		add_env(env_list, creat_env(ft_strdup("SHLVL"), ft_strdup("1")));
	else
		updat_value_shl(env_list, "SHLVL", ft_itoa(shell_level(tmp)));
}
