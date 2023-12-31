/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:33:17 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/21 00:46:01 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_herd_rd_in(t_substruct **cmd, t_cmd *ls, t_data *nv)
{
	if ((*cmd)->next)
		(*cmd) = (*cmd)->next;
	here_doc("tmp", (*cmd)->data, nv, ls);
	ls->filein = open("tmp", O_RDONLY, 0644);
}

int	herd_rd_in(t_cmd *ls, t_substruct **cmd, t_data *nv)
{
	char	*new;

	if (ls->filein)
		close (ls->filein);
	if ((*cmd)->type == heredoc)
		help_herd_rd_in(cmd, ls, nv);
	else
	{
		new = subc_quots((*cmd)->next->data);
		if (access(new, F_OK) == -1)
			return (message_error("minishell : ", new, \
			": No such file or directory\n"), free(new), nv->exit_status = 1, 0);
		else
		{
			ls->filein = open(new, O_RDONLY, 0644);
			if (ls->filein == -1)
				return (free(new), perror("open"), close(ls->filein), 0);
		}
		ft_free_str(new);
	}
	return (1);
}

char	*getlastcmd(t_cmd *cmd)
{
	t_cmd		*cm;
	t_substruct	*subs;
	char		*str;

	cm = cmd;
	if (cm)
	{
		subs = cm->s_substruct;
		while (subs->next)
			subs = subs->next;
		if (subs->prev && (subs->prev->type == rd_output || \
		(subs->prev->prev && subs->prev->type == rd_output \
		&& subs->prev->prev->type == rd_output)))
		{
			str = ft_strdup(subs->data);
			return (str);
		}
	}
	return (NULL);
}

void	help_get_rd(t_substruct **cmd, t_tmp *var, t_data *nv)
{
	char	*new;
	t_check	*tmp;

	tmp = (t_check *)malloc(sizeof(t_check));
	if (!tmp)
		return ;
	close(var->fds[var->ls->i][1]);
	new = subc_quots((*cmd)->next->data);
	tmp->name_fd = new;
	tmp->permession = 0644;
	if ((*cmd)->type == rd_output)
	{
		tmp->mode = (O_RDWR | O_CREAT | O_TRUNC);
		var->ls->fileout = ft_check_fils(tmp, nv);
	}
	else
	{
		tmp->mode = (O_RDWR | O_CREAT | O_APPEND);
		var->ls->fileout = ft_check_fils(tmp, nv);
	}
	free (tmp);
	ft_free_str(new);
}

int	help_get_rd2(t_tmp *var, t_substruct **cmd, t_data *nv)
{
	if (!herd_rd_in(var->ls, cmd, nv) || g_flag_signal == 1)
		return (nv->exit_status = 1, 0);
	return (1);
}
