/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:30:16 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/10/17 22:19:24 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handller(int use_less)
{
	(void)use_less;
	if (waitpid(0, NULL, WNOHANG))
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_flag_signal = 5;
	}
}

void	signal_init(void)
{
	g_flag_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handller);
}

void	signals_in_child_process(int status, t_data *nv)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("\\Quit: 3\n", 1);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 1);
		if (WTERMSIG(status) == 11)
			ft_putstr_fd("Segmentation fault: 11\n", 2);
		nv->exit_status = WTERMSIG(status) + 128;
	}
	else 
		nv->exit_status = WEXITSTATUS(status);
}

int	checkrd(t_cmd *tmp, t_substruct *tmps, int **fds, t_data *nv)
{
	int		fd;

	signal (SIGINT, sigint_herdoc);
	fd = dup(0);
	if (!checkrdnorm(tmps, nv, fds, tmp))
	{
		close (fd);
		return (0);
	}
	if (!isatty(0))
	{
		nv->exit_status = 1;
		dup2(fd, 0);
		close(fd);
		signal (SIGINT, sig_handller);
		return (0);
	}
	close (fd);
	nv->exit_status = 1;
	signal (SIGINT, sig_handller);
	return (1);
}
