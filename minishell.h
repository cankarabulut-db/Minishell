/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:35:09 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/01 19:48:06 by akar             ###   ########.fr       */
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
	char				**input;
	char				**heredoc;
	char				**output;
	char				**append;
	char				**args;
	char				**env;
	int					status;
	int pid;
	char **execve_args;
	struct s_env		*main_env;
	struct s_shell		*next;
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

int		ft_exist(char *str, char a, int i);	
int		ft_strplen(char **str);
void	split_pipe_and_fill(t_shell *cmd, char *str, int i, t_rdr *listsize);
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

#endif