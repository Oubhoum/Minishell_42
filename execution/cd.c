/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:12:59 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/21 01:15:20 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	pwd_update(t_data *nv, char *str1, char *str2)
{
	updat_value(&(nv->environement), "PWD", str2);
	updat_value(&(nv->environement), "OLDPWD", str1);
}

static	void	cd_home(t_data *nv, t_environement *env, char *str1, char *str2)
{
	t_environement	*tmp_env;

	tmp_env = env;
	if (!tmp_env)
		return ;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->cle, "HOME") == 0)
		{
			getcwd(str1, 1024);
			if (chdir(tmp_env->valeur) == -1)
				ft_perror("Changing directory to home failled", nv);
			else
			{
				getcwd(str2, 1024);
				pwd_update(nv, str1, str2);
			}
			break ;
		}
		tmp_env = tmp_env->next;
	}
}

int	check_currpath(char *str1, char *option, t_data *nv)
{
	if (access(str1, F_OK) == -1 && option && !ft_strcmp(option, "."))
	{
		perror("cd");
		return (0);
	}
	if (chdir(option) == -1)
	{
		ft_perror("Changing directory failled", nv);
		return (0);
	}
	return (1);
}

void	ft_cd(char **option, t_data *nv)
{
	char	str1[1024];
	char	str2[1024];

	nv->exit_status = 0;
	if (option && ft_strcmp(option[0], "cd") == 0 && !option[1])
	{
		if (if_key_exist(nv->environement, "HOME"))
		{
			ft_perror("HOME not set", nv);
			return ;
		}
		cd_home(nv, nv->environement, str1, str2);
	}
	else if (option && ft_strcmp(option[0], "cd") == 0)
	{
		getcwd(str1, 1024);
		if (!check_currpath(str1, option[1], nv))
			return ;
		else
		{
			getcwd(str2, 1024);
			pwd_update(nv, str1, str2);
		}
	}
}
