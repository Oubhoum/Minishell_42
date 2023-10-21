/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:33:30 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/17 14:38:36 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **option, t_data *nv, t_cmd *cmd)
{
	t_environement	*tmp_env;

	tmp_env = nv->environement;
	if (!tmp_env)
		return ;
	nv->exit_status = 0;
	if (option && ft_strcmp(option[0], "env") == 0 && !option[1])
	{
		while (tmp_env)
		{
			if (tmp_env->valeur)
			{
				ft_putstr_fd(tmp_env->cle, cmd->fileout);
				write(cmd->fileout, "=", 1);
				ft_putstr_fd(tmp_env->valeur, cmd->fileout);
				write(cmd->fileout, "\n", 1);
			}
			tmp_env = tmp_env->next;
		}
	}
}
