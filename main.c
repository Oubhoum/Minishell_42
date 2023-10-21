/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:28 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/20 22:19:28 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_flag_signal;

int	check_linesps(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\f'
			&& line[i] != '\v' && line[i] != '\n' && line[i] != '\r' )
			return (1);
		i++;
	}
	free (line);
	return (0);
}

void	help_main( char *line, char **ptr, t_cmd *list, t_data *nv)
{
	if (ft_strlen(line))
	{
		if (get_cmds(line, &list, nv) && syntaxe_error(list, nv))
			ft_execution(list, ptr, nv);
		free_env_values(ptr);
		free_list (&list);
	}
	else
	{
		free(line);
		free_env_values(ptr);
	}
}

int	init_check_var(char **line, char **new_line, int ac, char *av)
{
	*line = NULL;
	*new_line = NULL;
	if (ac != 1)
	{
		message_error("minishell: ", av, \
		": No such file or directory\n");
		return (0);
	}
	return (1);
}

void	instruction_errmain(int exitstatus)
{
	write(1, "exit\n", 5);
	exitstatus = 0;
	exit (exitstatus);
}

int	main(int ac, char **av, char **env)
{
	t_norm	q;

	q.list = NULL;
	q.ptr = NULL;
	if (!init_check_var(&q.line, &q.new_line, ac, av[1]))
		return (0);
	q.nn.environement = env_remplissage(env);
	q.nn.exit_status = 0;
	rl_catch_signals = 0;
	signal_init();
	while (1)
	{
		q.line = readline(LINE);
		ft_func(&q.nn.exit_status);
		if (!q.line)
			instruction_errmain(q.nn.exit_status);
		if (!check_linesps(q.line))
			continue ;
		add_history(q.line);
		q.ptr = get_env_values_table(q.nn.environement);
		q.new_line = option_expand(q.line, q.ptr, &q.nn);
		help_main(q.new_line, q.ptr, q.list, &q.nn);
	}
	return (0);
}
