/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:41:59 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/21 01:25:49 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_herdoc(int sig)
{
	(void)sig;
	close (0);
}

int	help(char *tmps, t_data *nv)
{
	int		fl;
	t_check	*tmp;

	tmp = (t_check *) malloc(sizeof(t_check));
	if (!tmp)
		return (-1);
	tmp->name_fd = tmps;
	tmp->mode = (O_CREAT | O_RDWR | O_TRUNC);
	tmp->permession = 0644;
	fl = ft_check_fils(tmp, nv);
	free (tmp);
	return (fl);
}

void	help2(char *str, int fl, t_cmd *l, t_data *nv)
{
	char	**ptr;
	char	*tmp;

	ptr = get_env_values_table(nv->environement);
	if (check_doll(str, '$') && l->herd != 1)
	{
		tmp = str;
		str = option_expand(tmp, ptr, nv);
	}
	write(fl, str, ft_strlen(str));
	write(fl, "\n", 1);
	if (str)
		free (str);
	free_env_values(ptr);
}

void	here_doc(char *tmps, char *end, t_data *nv, t_cmd *ls)
{
	int		fl;
	char	*str;

	fl = help(tmps, nv);
	str = readline("> ");
	if (fl != -1 && !ft_strcmp(end, " "))
		write(fl, str, ft_strlen(str));
	while (fl != -1 && str && ft_strcmp(str, end) && isatty(0))
	{
		help2(str, fl, ls, nv);
		str = readline("> ");
		if (!str)
		{
			ft_free_str(str);
			break ;
		}
	}
	free(str);
	close (fl);
}
