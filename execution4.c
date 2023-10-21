/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:35:15 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/21 00:47:59 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_get_rd3(t_substruct **cmd, t_tmp *var, t_data *nv)
{
	int	is_tr;

	is_tr = 0;
	if ((*cmd)->type == heredoc || \
	((*cmd)->type == rd_input))
	{
		if (!help_get_rd2(var, cmd, nv))
			return (0);
		is_tr = 1;
	}
	else if (!is_tr && var->ls && var->ls->prev)
		var->ls->filein = var->fds[var->ls->i - 1][0];
	return (1);
}

int	get_rd(t_substruct **cmd, t_tmp *var, t_data *nv)
{
	int		is_tr;

	is_tr = 0;
	if (!help_get_rd3(cmd, var, nv))
		return (0);
	is_tr = 0;
	if (((*cmd) && (*cmd)->type == rd_output)
		|| ((*cmd) && (*cmd)->type == rd_output_append))
	{
		help_get_rd(cmd, var, nv);
		if (var->ls->fileout == -1)
			return (0);
		is_tr = 1;
		(*cmd) = (*cmd)->next;
	}
	if (!is_tr && var->ls && var->ls->next)
		var->ls->fileout = var->fds[var->ls->i][1];
	return (1);
}

char	*get_str1(char *cmd, int *i, t_cmd *l, int flag)
{
	t_qvar	*qvr;
	char	*str;

	qvr = init_qvar();
	if (!qvr)
		return (NULL);
	while (cmd[*i] && cmd[*i] != ' ')
	{
		if (cmd[*i] == SQUOTE || cmd[*i] == DQUOTES)
		{
			if (l->herd == 0)
				l->herd = 1;
			def_flag_pre(cmd[*i], qvr);
			(*i)++;
			qvr->str = get_inside_quotes(cmd, i, qvr->type);
			(*i)++;
		}
		if (cmd[*i] && is_alpha(cmd[*i]))
			qvr->rest = get_outside_quotes(cmd, i);
		if (!qvr->str && !qvr->rest && flag)
			qvr->str = ft_strdup(" ");
		join_result(&qvr);
	}
	str = qvr->result;
	return (free (qvr), str);
}

char	*get_str2(char *cmd, int *i, t_data *nv, t_cmd *l)
{
	char	*str;

	str = NULL;
	l->herd = -1;
	str = get_redirection(cmd, &(*i));
	if (ft_strlen(str) > 2 || ft_strlen(str) < 1)
	{
		error_str(str, nv);
		free(str);
		return (NULL);
	}
	if (ft_strlen(str) == 2 && str[0] == '<' && str[1] == '<')
		l->herd = 0;
	return (str);
}
