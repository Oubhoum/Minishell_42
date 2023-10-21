/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:23:38 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/17 13:06:47 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char **option, t_data *nv, t_cmd *cmd)
{
	char	wd[1024];
	int		i;

	nv->exit_status = 0;
	i = 0;
	if (option && !ft_strcmp(option[0], "pwd"))
	{
		getcwd(wd, sizeof(wd));
		ft_putstr_fd(wd, cmd->fileout);
		write(cmd->fileout, "\n", 1);
	}
}
