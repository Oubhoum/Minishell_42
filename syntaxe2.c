/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:52:08 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/17 17:31:10 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_redirection(char *cmd, int *start)
{
	char	*ret;
	int		size;
	int		i;

	i = (*start);
	size = 0;
	while (cmd[*start] && (cmd[*start] == '>' || cmd[*start] == '<'))
	{
		size++;
		(*start)++;
	}
	ret = ft_substr(cmd, i, size);
	return (ret);
}

char	*get_command1(char *cmd, int *start)
{
	char	*tmp;
	int		size;
	int		i;

	tmp = NULL;
	size = 0;
	i = *start;
	while (cmd[*start] && cmd[*start] != ' ' && cmd[*start] != '\t'
		&& cmd[*start] != '>' && cmd[*start] != '<'
		&& cmd[*start] != DQUOTES && cmd[*start] != SQUOTE)
	{
		size++;
		(*start)++;
	}
	tmp = ft_substr(cmd, i, size);
	return (tmp);
}

void	message_error(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd(s3, 2);
}

void	error_str(char *str, t_data *nv)
{
	if (str[0] == '>' && str[1] == '>')
	{
		nv->exit_status = 258;
		write(2, "minishell: syntax error", 23);
		write(2, "near unexpected token `>>'\n", 27);
	}
	if (str[0] == '<' && str[1] == '<')
	{
		nv->exit_status = 258;
		write(2, "minishell: syntax error", 23);
		write(2, "near unexpected token `<<'\n", 27);
	}
}

int	message_erreur(char *str, t_data *nv)
{
	ft_putstr_fd("minisell : exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	nv->exit_status = 255;
	return (nv->exit_status);
}
