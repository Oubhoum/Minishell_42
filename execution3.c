/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:34:26 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/12 23:50:59 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_cmd *ls)
{
	if (ls->filein != 0)
		close (ls->filein);
	if (ls->fileout != 1)
		close (ls->fileout);
}

void	ft_free_matrix(int **str, int size, int flg)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(str[i][0]);
		close(str[i][1]);
		free (str[i]);
		i++;
	}
	if (flg && str[i])
		free (str[i]);
	free (str);
}

int	ft_creat_pipe(int size, int **fds, t_data *nv)
{
	int	i;

	i = 0;
	nv->error = 0;
	while (i < size)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds)
			return (0);
		if (pipe(fds[i]) == -1)
		{
			nv->error = 1;
			(ft_free_matrix(fds, i, nv->error), write(2, "error piping\n", 14));
			nv->exit_status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	free_execution(t_varn *var, t_cmd *list)
{
	if (var->fds)
		ft_free_matrix(var->fds, ft_lstsize(list), 0);
	(free (var->pd), free(var));
}

t_varn	*init_var(t_cmd *list, t_data *nv)
{
	t_varn	*var;

	var = (t_varn *)malloc(sizeof(t_varn));
	if (!var)
		return (NULL);
	var->i = 0;
	var->size = ft_lstsize(list);
	var->fds = (int **)malloc(sizeof(int *) * (var->size));
	if (!var->fds)
		return (NULL);
	var->pd = (int *)malloc(sizeof(int) * (var->size));
	if (!var->pd)
		return (NULL);
	if (!ft_creat_pipe(ft_lstsize(list), var->fds, nv))
	{
		free (var->pd);
		free (var);
		var = NULL;
		return (NULL);
	}
	return (var);
}
