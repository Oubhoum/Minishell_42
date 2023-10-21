/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 16:32:23 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/21 02:47:10 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <paths.h>

# define DQUOTES 34
# define SQUOTE 39
# define LINE "minishell:$ "

typedef enum e_types
{
	pip,
	word,
	rd_input,
	rd_output,
	rd_output_append,
	heredoc,
	newline
}	t_types;

typedef struct s_subStruct
{
	char				*data;
	int					type;
	int					cls;
	struct s_subStruct	*next;
	struct s_subStruct	*prev;
}	t_substruct;

typedef struct s_cmd{
	char			*data;
	int				i;
	pid_t			*pd;
	int				**fds;
	t_substruct		*s_substruct;
	int				filein;
	int				fileout;
	struct s_cmd	*next;
	int				herd;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_environement
{
	char					*env;
	char					*cle;
	char					*valeur;
	struct s_environement	*next;
	char					*key;
	char					*key1;
	char					*val;
	char					*val_app;
}	t_environement;

typedef struct s_data
{
	int				exit_status;
	t_environement	*environement;
	int				error;
}	t_data;

extern int	g_flag_signal;

typedef struct s_tmp
{
	int		**fds;
	t_cmd	*ls;
}	t_tmp;

typedef struct s_expand{
	int		size;
	int		start;
	char	*str;
	char	*tmp;
	char	*ret;
	char	*ret1;
	char	*value;
	int		sdq;
}t_expand;

typedef struct s_qvar
{
	char	*result;
	char	*str;
	char	*rest;
	char	*tmp;
	int		type;
}t_qvar;

typedef struct s_varn
{
	char		**option;
	int			**fds;
	pid_t		*pd;
	int			size;
	int			i;
}t_varn;

typedef struct s_check
{
	char	*name_fd;
	int		mode;
	int		permession;
}	t_check;

typedef struct s_export
{
	char	*var;
	int		i;
}	t_export;

typedef struct s_var
{
	int	flag1;
	int	flag2;
	int	flag3;
	int	flag4;
	int	flag5;
}	t_var;

typedef struct s_norm
{
	char			*line;
	char			*new_line;
	t_cmd			*list;
	char			**ptr;
	t_data			nn;
}	t_norm;

void			sigint_herdoc(int sig);
char			**ft_split(char *s, char c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_get_path(char *argv, char **env);
int				get_ev(char **env);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(const char *s);
char			*ft_substr(char *s, unsigned int start, size_t len);
int				syntaxe_error(t_cmd *ls, t_data *nv);
t_cmd			*ft_lstnew(char *cmd, t_data *nv);
int				ft_lstsize(t_cmd *lst);
t_cmd			*ft_lstlast(t_cmd *lst);
void			ft_lstadd_back(t_cmd **lst, t_cmd *new);
int				get_type(char *s);
t_substruct		*n_lstnew(char *cmd);
int				n_lstsize(t_substruct *lst);
t_substruct		*n_lstlast(t_substruct *lst);
void			n_lstadd_back(t_substruct **lst, t_substruct *new);
char			*get_redirection(char *cmd, int *start);
char			*get_command(char *cmd, int *start, t_cmd *l);
char			*ft_strtrim(char *s1, char *set);
void			free_sublist(t_substruct **substruct);
void			free_list(t_cmd **substruct);
void			exec_chile(char **option, char **env, t_cmd *list, t_data *nv);
void			here_doc(char *tmps, char *end, t_data *nv, t_cmd *l);
void			ft_free(char **str);
int				ft_check_fils(t_check *check, t_data *nv);
void			ft_execution(t_cmd *list, char **env, t_data *nv);
char			**__resize(char **Array, char *new);
void			ft_close(t_cmd *ls);
void			ft_close_pipe(t_cmd *ls, int **fds);
int				get_rd(t_substruct **cmd, t_tmp *var, t_data *nv);
int				find_equal_or_plus(char *s, char c);
void			ft_cd(char **option, t_data *nv);
void			ft_echo(char **option, t_data *nv, t_cmd *cmd);
void			ft_env(char **option, t_data *nv, t_cmd *cmd);
void			ft_exit(char **option, t_data *nv);

int				ft_strcmp(char *s1, char *s2);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
void			ft_pwd(char **option, t_data *nv, t_cmd *cmd);
void			ft_unsit(char **option, t_data *nv);
void			free_environement(t_data *nv);
void			ft_export(char **option, t_data *nv, t_cmd *cmd);
void			updat_value(t_environement **env, char *cle, char *valeur);
int				if_key_exist(t_environement *env, char *cle);
void			creat_node(t_environement **env, char *s1, char *s2);
size_t			get_value_len(char *str);
char			*get_key(char *str);
char			*get_value_ex(char *str);
int				is_append(char *str);
void			ft_append(t_environement **env, char *cle, char *valeur);
char			*get_key_append(char *str);
char			*get_value_append(char *str);
int				check_key_parssing(char *str);
size_t			get_ferst_equal_posetion(char *str);
int				ftt_strchr(const char *s, int c);
int				check_builtins(t_cmd *cmd, char **option, t_data *nv);
char			*subc_quots(char *str);
char			*ft_itoa(int n);
void			signals_in_child_process(int status, t_data *nv);
void			message_error(char *s1, char *s2, char *s3);
void			message_error(char *s1, char *s2, char *s3);
int				get_cmds(char *line, t_cmd **list, t_data *nv);
int				check_linesps(char *line);
int				check_doll(char *str, char c);
void			ft_free_str(char *str);
int				is_alpha(char c);
void			free_env_values(char **env_values);
int				ft_creat_pipe(int size, int **fds, t_data *nv);
void			ft_free_matrix(int **str, int size, int flg);
void			ft_close(t_cmd *ls);
int				help_get_rd3(t_substruct **cmd, t_tmp *var, t_data *nv);
int				help_get_rd2(t_tmp *var, t_substruct **cmd, t_data *nv);
char			*getlastcmd(t_cmd *cmd);
void			help_get_rd(t_substruct **cmd, t_tmp *var, t_data *nv);
char			*get_str1(char *cmd, int *i, t_cmd *l, int flag);
int				help_get_cmds(char *line, t_cmd **list, t_data *nv);
int				check_linesps(char *line);
int				check_doll(char *str, char c);
void			ft_free_str(char *str);
int				is_alpha(char c);
int				ft_size_nam(char *str, char c);
void			free_env_values(char **env_values);
char			*option_expand(char *line, char **env, t_data *nv);
void			ft_dup(t_cmd *ls, char **option, char **env, t_data *nv);
void			error_str(char *str, t_data *nv);
void			get_option(char ***option, t_substruct *tmps);
int				checkrd(t_cmd *tmp, t_substruct *tmps, int **fds, t_data *nv);
void			wait_pd(t_varn *var, int size, t_data *nv);
char			*get_str2(char *cmd, int *i, t_data *nv, t_cmd *l);
char			*get_inside_quotes(char *cmd, int *i, int type);
char			*get_outside_quotes(char *cmd, int *i);
int				len_wordsplit(char *s, int **j, char c);
void			malloc_wordspl(char **cases, int len, \
int *found_s, int *found_d);
char			*get_redirection(char *cmd, int *start);
int				ft_isalpha(int c);
char			*get_command1(char *cmd, int *start);
int				line_filpip(char *line);
int				non_closed_quotes(char *line);
void			free_execution(t_varn *var, t_cmd *list);
void			def_flag_pre(char c, t_qvar *qvr);
void			join_result(t_qvar	**qvr);
t_qvar			*init_qvar(void);
t_varn			*init_var(t_cmd *list, t_data *nv);
t_environement	*env_remplissage(char **env_array);
void			ft_perror(char *str, t_data *nv);
void			signal_init(void);
char			**get_env_values_table(t_environement *env);
void			free_2d_char_array(char **array);
int				ft_atoi(char *str);
char			*getenvalue(char *name, char **env);
int				ft_isalnum(int c);
int				ft_isdigitt(int c);
int				ft_isalphaa(int c);
void			init_x(t_environement **tmp_env, char *str);
void			free_x(char *s1, char *s2, char *s3, char *s4);
void			print_env(t_environement *env, t_cmd *cmd);
void			init_expan_data(int *var_quot, char *line, int i);
void			sig_handller(int use_less);
void			initsqd(int *sdq);
int				checkrdnorm(t_substruct *tmps, t_data *nv, \
int **fds, t_cmd *tmp);
void			ft_func(int *exit_st);
void			env_is_empty(t_environement **env_list);
void			add_variables(t_environement **env_list);
void			add_env(t_environement **env_list, t_environement *env_node);
t_environement	*creat_env(char *cle, char *valeur);
int				error_mulrd(char *line, int i, t_data *nv);
char			*ret_result_exp(char *tmp);
char			*addchar_tostr(char *str, char c);
void			falg_of_expval(char *line, int i, int *j);
char			*return_namexp(char *line, int *j);
#endif