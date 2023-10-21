/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:52:56 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/21 12:37:01 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print(t_environement *env, t_cmd *cmd)
{
	if (env && env->cle != NULL && env->valeur == NULL
		&& ft_strcmp(env->cle, ""))
	{
		ft_putstr_fd("declare -x ", cmd->fileout);
		ft_putstr_fd(env->cle, cmd->fileout);
		write(cmd->fileout, "\n", 1);
	}
	else if (env && env->cle && env->valeur && ft_strcmp(env->cle, ""))
	{
		ft_putstr_fd("declare -x ", cmd->fileout);
		ft_putstr_fd(env->cle, cmd->fileout);
		write(cmd->fileout, "=\"", 2);
		ft_putstr_fd(env->valeur, cmd->fileout);
		write(cmd->fileout, "\"\n", 2);
	}
}

void	print_env(t_environement	*env, t_cmd *cmd)
{
	t_environement	*tmp_env;
	t_environement	*tmp_env2;
	char			*tmp_key;
	char			*tmp_value;

	tmp_env = env;
	while (tmp_env)
	{
		tmp_env2 = tmp_env->next;
		while (tmp_env2)
		{
			if (ft_strcmp(tmp_env->cle, tmp_env2->cle) > 0)
			{
				tmp_key = tmp_env->cle;
				tmp_env->cle = tmp_env2->cle;
				tmp_env2->cle = tmp_key;
				tmp_value = tmp_env->valeur;
				tmp_env->valeur = tmp_env2->valeur;
				tmp_env2->valeur = tmp_value;
			}
			tmp_env2 = tmp_env2->next;
		}
		ft_print(tmp_env, cmd);
		tmp_env = tmp_env->next;
	}
}
