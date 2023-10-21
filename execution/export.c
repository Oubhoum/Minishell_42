/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:17:04 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/21 13:26:04 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_key_exist(t_environement *env, char *cle)
{
	t_environement	*tmp_env;

	tmp_env = env;
	if (!cle || !tmp_env)
		return (1);
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->cle, cle) == 0)
			return (0);
		tmp_env = tmp_env->next;
	}
	return (1);
}

void	updat_value(t_environement **env, char *cle, char *valeur)
{
	t_environement	*tmp_env;

	tmp_env = *env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->cle, cle) == 0)
		{
			if (tmp_env->valeur)
				free(tmp_env->valeur);
			tmp_env->valeur = ft_strdup(valeur);
			break ;
		}
		tmp_env = tmp_env->next;
	}
}

void	handel_25_line(char **option, t_environement **env, int i)
{
	t_var	x;

	x.flag1 = ftt_strchr(option[i], '=');
	x.flag2 = if_key_exist(*env, (*env)->key);
	x.flag3 = if_key_exist(*env, (*env)->key1);
	x.flag4 = is_append(option[i]);
	x.flag5 = get_ferst_equal_posetion(option[i]);
	if (option && !ft_strcmp(option[0], "export") && option[i])
	{
		if (!x.flag4 && x.flag5 && x.flag2 && x.flag1)
			creat_node(env, (*env)->key, (*env)->val);
		else if (!x.flag4 && x.flag5 && !x.flag2 && x.flag1)
			updat_value(env, (*env)->key, (*env)->val);
		else if (!x.flag5 && x.flag2 && !x.flag1)
			creat_node(env, (*env)->key, NULL);
		else if (!x.flag4 && x.flag5 && x.flag2)
			creat_node(env, (*env)->key, (*env)->val);
		else if (x.flag4 && x.flag5 && !x.flag3)
			ft_append(env, (*env)->key1,
				(*env)->val_app);
		else if (x.flag4 && x.flag3 && x.flag5)
			creat_node(env, (*env)->key1,
				(*env)->val_app);
	}
	free_x((*env)->key, (*env)->key1, (*env)->val_app, (*env)->val);
}

t_environement	*if_env_is_empty(t_environement **env)
{
	t_environement	*tmp_env;

	tmp_env = NULL;
	add_env(env, creat_env(ft_strdup(""), NULL));
	tmp_env = *env;
	return (tmp_env);
}

void	ft_export(char **option, t_data *nv, t_cmd *cmd)
{
	int				i;
	t_environement	*tmp_env;

	tmp_env = nv->environement;
	if (!tmp_env)
		tmp_env = if_env_is_empty(&nv->environement);
	nv->exit_status = 0;
	i = 1;
	while (option[i])
	{
		init_x(&tmp_env, option[i]);
		if ((!check_key_parssing(tmp_env->key)
				&& !is_append(option[i])) || (!check_key_parssing(tmp_env->key1)
				&& is_append(option[i])))
		{
			ft_perror("Invalide key", nv);
			free_x(tmp_env->key, tmp_env->key1, tmp_env->val_app, tmp_env->val);
		}
		else
			handel_25_line(option, &tmp_env, i);
		i++;
	}
	if (option && !ft_strcmp(option[0], "export") && !option[1])
		print_env(tmp_env, cmd);
}
