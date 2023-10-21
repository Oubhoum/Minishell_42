/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_remlissage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:00:27 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/17 13:09:54 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_environement	*get_last_node_env(t_environement *env_list)
{
	if (!env_list)
		return (NULL);
	while (env_list->next)
		env_list = env_list->next;
	return (env_list);
}

void	add_env(t_environement **env_list, t_environement *env_node)
{
	t_environement	*env_list_tmp;

	if (env_list)
	{
		if (*env_list)
		{
			env_list_tmp = get_last_node_env(*env_list);
			env_list_tmp->next = env_node;
		}
		else
			*env_list = env_node;
	}
	else
		return ;
}

t_environement	*creat_env(char *cle, char *valeur)
{
	t_environement	*env_list;

	env_list = malloc(sizeof(t_environement));
	if (!env_list)
		return (0);
	env_list->cle = cle;
	env_list->valeur = valeur;
	env_list->next = NULL;
	return (env_list);
}

t_environement	*env_remplissage(char **env_array)
{
	int				i;
	int				index;
	t_environement	*env_list;

	env_list = NULL;
	if (!env_array[0])
		env_is_empty(&env_list);
	else
	{
		i = 0;
		index = 0;
		while (env_array[i])
		{
			index = ft_strlen(env_array[i])
				- get_ferst_equal_posetion(env_array[i]); 
			add_env(&env_list, creat_env(ft_substr(env_array[i], 0,
						get_ferst_equal_posetion(env_array[i])),
					ft_substr(env_array[i],
						get_ferst_equal_posetion(env_array[i]) + 1, index)));
			i++;
		}
	}
	add_variables(&env_list);
	return (env_list);
}

int	check_builtins(t_cmd *cmd, char **option, t_data *nv)
{
	if (cmd->s_substruct && !ft_strcmp("pwd", cmd->s_substruct->data))
		return (ft_pwd(option, nv, cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("echo", cmd->s_substruct->data))
		return (ft_echo(option, nv, cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("env", cmd->s_substruct->data))
		return (ft_env(option, nv, cmd), 1);
	if (cmd->s_substruct && !ft_strcmp("exit", cmd->s_substruct->data))
		return (ft_exit(option, nv), 1);
	if (cmd->s_substruct && !ft_strcmp("unset", cmd->s_substruct->data))
		return (ft_unsit(option, nv), 1);
	if (cmd->s_substruct && !ft_strcmp("cd", cmd->s_substruct->data))
		return (ft_cd(option, nv), 1);
	if (cmd->s_substruct && !ft_strcmp("export", cmd->s_substruct->data))
		return (ft_export(option, nv, cmd), 1);
	return (0);
}
