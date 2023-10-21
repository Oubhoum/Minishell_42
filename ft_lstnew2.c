/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:14:54 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/16 21:25:59 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_filpip(char *line)
{
	char	*str;

	if (non_closed_quotes(line))
		return (0);
	if (line[ft_strlen(line) - 1] == '|'
		&& ft_strlen(line) > 1 && line[0] != '>' && line[0] != '|')
	{
		str = line;
		line = ft_strjoin(str, " newline");
		ft_putstr_fd("minishell: syntax error: unexpected end of file \n", 2);
		free (str);
		free(line);
		return (0);
	}
	return (1);
}

t_qvar	*init_qvar(void)
{
	t_qvar	*qvr;

	qvr = (t_qvar *)malloc(sizeof(t_qvar));
	if (!qvr)
		return (NULL);
	(qvr)->result = NULL;
	(qvr)->str = NULL;
	(qvr)->rest = NULL;
	return (qvr);
}

void	join_result(t_qvar	**qvr)
{
	char	*tmp;

	(*qvr)->tmp = ft_strjoin((*qvr)->str, (*qvr)->rest);
	free ((*qvr)->str);
	(*qvr)->str = NULL;
	free ((*qvr)->rest);
	(*qvr)->rest = NULL;
	tmp = (*qvr)->result;
	(*qvr)->result = ft_strjoin((*qvr)->result, (*qvr)->tmp);
	free (tmp);
	free ((*qvr)->tmp);
	(*qvr)->tmp = NULL;
}

void	def_flag_pre(char c, t_qvar *qvr)
{
	if (c == SQUOTE)
		qvr->type = SQUOTE;
	if (c == DQUOTES)
		qvr->type = DQUOTES;
}
