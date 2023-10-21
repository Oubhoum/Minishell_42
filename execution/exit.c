/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:43:16 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/20 20:46:04 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ftt_isdigit(int c)
{
	return ('0' <= c && '9' >= c);
}

static	int	my_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ftt_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(char **option, t_data *nv)
{
	nv->exit_status = 0;
	write(1, "exit\n", 5);
	if (option && !ft_strcmp(option[0], "exit") && !option[1])
		exit(nv->exit_status);
	else if (option && !ft_strcmp(option[0], "exit") && option[2])
	{
		write(2, "too many arguments\n", 19);
		if (!my_isdigit(option[1]))
			exit(1);
	}
	else if (option && !ft_strcmp(option[0], "exit") && option[1])
	{
		if (!my_isdigit(option[1]))
		{
			write(2, "numeric argument required\n", 26);
			exit(255);
		}
		else
			exit(ft_atoi(option[1]));
	}
}
