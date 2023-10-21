/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:40:46 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/21 02:46:36 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*addchar_tostr(char *str, char c)
{
	char	*tmp;
	int		strsize;
	int		i;

	strsize = 0;
	if (str)
		strsize = ft_strlen(str);
	tmp = (char *)malloc (sizeof(char) * strsize + 2);
	i = 0;
	while (i < strsize)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	i++;
	tmp[i] = '\0';
	if (str)
		free (str);
	return (tmp);
}

void	get_var_name(char *line, int *j, t_expand *exp, char **env)
{
	char	*tmp;
	char	*name;
	char	*result;

	*j = 0;
	name = NULL;
	tmp = NULL;
	if (*line == '$')
	{
		*j = 1;
		name = return_namexp(line, j);
		tmp = getenvalue(name, env);
		if (!tmp && exp->sdq)
			tmp = ft_strdup(" ");
		result = ret_result_exp(tmp);
		if (tmp && !ft_strcmp(tmp, " ") && exp->sdq)
			free (tmp);
		ft_free_str (name);
		name = exp->str;
		exp->str = ft_strjoin(name, result);
		free (name);
		free(result);
		return ;
	}
	exp->str = NULL;
}

void	help_option_expand(char *line, char **env, t_expand *exp)
{
	char	*tmp;
	int		sdq[4];
	int		j;

	initsqd(sdq);
	while (line[sdq[3]])
	{
		j = 0;
		init_expan_data(sdq, line, sdq[3]);
		falg_of_expval(line, sdq[3], &sdq[2]);
		if (line[sdq[3]] == '$' && (line[sdq[3] + 1]
				&& line[sdq[3] + 1] != '"') && !sdq[0] && !sdq[2])
		{
			exp->sdq = sdq[1];
			get_var_name(line + sdq[3], &j, exp, env);
		}
		sdq[3] += j;
		if (j == 0)
		{
			tmp = exp->str;
			exp->str = addchar_tostr(exp->str, line[sdq[3]]);
			sdq[3]++;
		}
	}
}

char	*expnad_exit_status(char *line, t_data *nv)
{
	int		sdq[4];
	char	*result;
	char	*tmp;
	char	*exits;

	exits = ft_itoa(nv->exit_status);
	result = NULL;
	initsqd(sdq);
	while (line[sdq[3]])
	{
		init_expan_data(sdq, line, sdq[3]);
		falg_of_expval(line, sdq[3], &sdq[2]);
		if (line[sdq[3]] == '$' && line[sdq[3] + 1] == '?'
			&& !sdq[0] && !sdq[2])
		{
			tmp = result;
			result = ft_strjoin(tmp, exits);
			free (tmp);
			sdq[3] += 2;
		}
		else
			result = addchar_tostr(result, line[sdq[3]++]);
	}
	return (free(exits), free(line), result);
}

char	*option_expand(char *line, char **env, t_data *nv)
{
	t_expand	*exp;
	char		*tmp;

	exp = (t_expand *)malloc(sizeof(t_expand));
	if (!exp)
		return (NULL);
	tmp = NULL;
	exp->str = NULL;
	if (!ft_strcmp(line, "$"))
		return (free(exp), line);
	line = expnad_exit_status(line, nv);
	help_option_expand(line, env, exp);
	tmp = ft_strtrim(exp->str, " ");
	ft_free_str (exp->str);
	free (line);
	return (free(exp), tmp);
}
