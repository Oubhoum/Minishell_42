/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:24:26 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/21 12:10:32 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_x(char *s1, char *s2, char *s3, char *s4)
{
	free(s1);
	free(s2);
	free(s3);
	free(s4);
}

void	init_x(t_environement **tmp_env, char *str)
{
	(*tmp_env)->key = get_key(str);
	(*tmp_env)->key1 = get_key_append(str);
	(*tmp_env)->val = get_value_ex(str);
	(*tmp_env)->val_app = get_value_append(str);
}

// env | cut -d= -f1 | tr '\n' ' '