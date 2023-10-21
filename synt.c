/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:43:22 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/21 02:46:52 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_mulrd(char *line, int i, t_data *nv)
{
	if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>')
	{
		write(2, "minishell: syntax error", 23);
		write(2, "near unexpected token `>>'\n", 27);
		ft_free_str(line);
		return (nv->exit_status = 258, 0);
	}
	if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] == '<')
	{
		write(2, "minishell: syntax error", 23);
		write(2, "near unexpected token `<<'\n", 27);
		ft_free_str(line);
		return (nv->exit_status = 258, 0);
	}
	return (1);
}

char	*ret_result_exp(char *tmp)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '|' || tmp[i] == '<' || tmp[i] == '>' )
		{
			result = addchar_tostr(result, '"');
			result = addchar_tostr(result, tmp[i]);
			result = addchar_tostr(result, '"');
			i++;
		}
		else
			result = addchar_tostr(result, tmp[i++]);
	}
	return (result);
}

void	falg_of_expval(char *line, int i, int *j)
{
	if (line [i] && line[i] == '<' && line[i + 1] && line[i + 1] == '<')
		*j = 1;
	else if (line[i] && line[i] != ' '
		&& line[i] != '$' && line[i] != '<' && line[i] != '"')
		*j = 0;
}

char	*return_namexp(char *line, int *j)
{
	char	*name;

	name = NULL;
	if (ft_isdigitt(line[*j]))
		name = addchar_tostr (name, line[*j++]);
	else
	{
		while (line[*j] && (ft_isalnum(line[*j]) || line[*j] == '_')
			&& line[*j] != '?')
			name = addchar_tostr (name, line[(*j)++]);
	}
	return (name);
}
