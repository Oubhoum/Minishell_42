/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:59:17 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/17 11:24:37 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_perror(char *str, t_data *nv)
{
	if (!str)
		return ;
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	nv->exit_status = 1;
}
