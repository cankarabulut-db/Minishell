/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:35:09 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/11 20:26:43 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "libft/libft.h"
#define DOLLAR 0
# define CHAR 1
# define DOUBLEQ 2
# define SINGLEQ 3
# define HEREDOC 4 // <<
# define APPEND 5 // >>
# define OUTPUT 6 // >
# define INPUT 7 // <
# define PIPE 8
# define MAIN_P 9
# define CHILD_P 10
# define HEREDOC_P 11 

typedef struct s_shell
{
	char				*cmd;
	int					ifd;
	int					ofd;
	char				**input;
	char				**heredoc;
	char				**output;
	char				**append;
	char				**args;
	char				**env;
	int					status;
	int					status1;
	int					fd_error;
	int 				pid;
	char 				**execve_args;
	char				*org_rdr;
	struct s_env		*main_env;
	struct s_shell		*next;


	int cur_i;
	int cur_o;
	int cur_ap;
}	t_shell;

typedef struct s_rdr
{
	int	ic;
	int	oc;
	int	ac;
	int	hc;
	int	icwhile;
	int	ocwhile;
	int	acwhile;
	int	hcwhile;
	int	type;
	int	listsize;
}	t_rdr;

typedef struct s_garbage
{
	void				*data;
	struct s_garbage	*next;
}				t_garbage;

typedef struct s_env
{
	char	**env;
}			t_env;

int g_global_exit;

int		ft_exist(char *str, char a, int i);	
int		ft_strplen(char **str);
int	split_pipe_and_fill(t_shell *cmd, char *str, int i, t_rdr *listsize);
int	error_msg(char *str1, int i);
int	start_parse(char *org_str, t_shell *cmd);
void	start_cmd(char **env);

void	empty_maker(char *str, char a, int start, int len);
void	struct_initializer(t_shell *cmd);

int	struct_filler(t_shell *cmd, char *str, int i);

int	input_output_control(char *str, int i);
int	heredoc_append_control(char *str, int i);
void	tokenize1(char *str, char *org_str, int i);
void	tokenize2(char *str, char *org_str, int i);
void	rdr_makezero(t_rdr *count);

char	*quote_remover(char *str, int i, int j);
int	quote_check(char *str);
int	pipe_ba(char *str, int i);
void	redirect_find_fill(t_shell *cmd, char *str, int i, t_rdr *rdrcount);
void	redirects_filler(t_shell *cmd, char *str, t_rdr *count, int i);
int		redirect_counter(char *str, int i, int redirectType);

void tab_to_space(char *str,int i);
void free_double_ptr(char **str);
int single_cmd_fill(t_shell *cmd, char *str, t_rdr *list);
void free_list(t_shell *cmd);
int is_quote(char a);
void args_quote_passer(char *str, int i);
void untokenizer_args(char **str, int i, int j);
void args_find_fill(t_shell *cmd, char *str);
int ft_print_s(char a);
void make_empty(char *str,int i);
void redirect_fill_null(t_shell *cmd,t_rdr *rc);
int check_redirect(char *pipe_cmd);
int is_quote(char a);
void redirect_size(t_rdr *rdrc, char *str);
void	redirect_malloc(t_shell *cmd, char *str, t_rdr *rdrc);
void redirect_fill_null(t_shell *cmd,t_rdr *rc);
void	redirects_filler(t_shell *cmd, char *str, t_rdr *count, int i);
void	redirect_find_fill(t_shell *cmd, char *str, int i, t_rdr *rdrcount);
int ft_rdrconfirmator(char redirect);
int	check_if_same(char *s1, char *s2);



char	*get_env_val(char *str, t_shell *cmd);
char	**check_dolar(char *org_str, t_shell *cmd);
char	*get_dollar(char *org_str, int *i, t_shell *cmd);
char *set_dolar(char *org_str, t_shell *cmd,size_t i,size_t temp);
///////////// ahmet
int get_path_index(t_shell *shell);
void	load_env_vars(t_shell *shell, char **environment);
char	*find_executable_path(t_shell *shell, int path_index);
char	**split_path_directories(t_shell *shell, int path_index);
void	free_path_directories(char **path_dirs);
void setup_redirections(t_shell *cmd);
void process_heredoc(t_shell *cmd);
void handle_heredoc(int status);
void handle_sigint(int sig);
void set_signal(int mode);
void handle_sigint(int sig);

//builtin
void throw_error(char **arg);
void if_not_null(char **arg, char *pwd, char *temppwd);
void	if_null(char *home, t_shell *mini, char *pwd);
void ft_cd(char **arg, t_shell *mini);
int flag_control(char *arg);
void echo_flag_control(char **arg, int *i);
void echo_with_arg(char **arg);
void ft_echo(char **arg);
int ft_strequ(const char *s1, const char *s2);
int find_env_index(char **env, char *var);
char *get_env(char **env, char *var);
void set_env(char **env, char *var, char *value);
int init_env(t_shell *mini, char **envp);
void ft_env(char **env, int status);
 int str_isdigit(char *str);
void ft_exit(char **arg);
int find_existing_env_var(t_shell *mini, const char *identifier);
int update_env_var(t_shell *mini, int j, const char *arg);
int check_env(t_shell *mini, const char *identifier, const char *arg);
int add_new_env(t_shell *mini, const char *arg, int j);
int valid_identifier(const char *str);
char *get_identifier(char *arg, char **equals_check);
int identifier_error(char **arg, char *identifier, int *i);
void mini_export_hlpr(t_shell *mini, char **arg, int i, char *identifier);
void ft_export(t_shell *mini, char **arg, int i, char *identifier);
void printpwd(void);
int is_builtin(char *cmd);
void execute_builtin(char **args, t_shell *mini);
size_t	ft_strarrlen(char **arr);
void	unset_env_var(char *var_name, t_shell  *mini);
int	is_file(const char *path);
int	is_directory(const char *path);

#endif