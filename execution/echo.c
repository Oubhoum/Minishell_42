/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 15:58:37 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/21 00:51:54 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	check_dash_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || !str[i + 1])
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

static	void	put_args(char **str, int i, int flag, t_cmd *cmd)
{
	if (!str)
		return ;
	while (str[i])
	{
		ft_putstr_fd(str[i++], cmd->fileout);
		if (str[i])
			write(cmd->fileout, " ", 1);
	}
	if (flag == 1)
		write(cmd->fileout, "\n", 1);
}

void	ft_echo(char **option, t_data *nv, t_cmd *cmd)
{
	int	i;

	i = 1;
	nv->exit_status = 0;
	while (option[i] && check_dash_n(option[i]))
		i++;
	if (i == 1)
		put_args(option, i, 1, cmd);
	else
		put_args(option, i, 44, cmd);
}
