/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:35:09 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/11 19:08:12 by nkarabul         ###   ########.fr       */
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
# define DOLLAR_O 14
# define DOLLAR_Q 15

typedef struct s_shell
{
	char				*cmd;
	char				**flags;
	char				**input;
	char				**heredoc;
	char				**output;
	char				**append;
	char				**args;
	char				**env;
	int					status;
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
void	error_msg(char *str1, int i);
void	start_parse(char *org_str, t_shell *cmd);
void	start_cmd(char **env);

void	empty_maker(char *str, char a, int start, int len);
void	struct_initializer(t_shell *cmd);

void	struct_filler(t_shell *cmd, char *str, int i);

void	input_output_control(char *str, int i);
void	heredoc_append_control(char *str, int i);
void	tokenize1(char *str, char *org_str, int i);
void	tokenize2(char *str, char *org_str, int i);
void	rdr_makezero(t_rdr *count);

char	*quote_remover(char *str, int i, int j);
void	quote_check(char *str);
void	pipe_ba(char *str, int i);
void	redirect_find_fill(t_shell *cmd, char *str, int i, t_rdr *rdrcount);
void	redirects_filler(t_shell *cmd, char *str, t_rdr *count, int i);
int		redirect_counter(char *str, int i, int redirectType);

void tab_to_space(char *str,int i);
void free_double_ptr(char **str);
void make_empty(char *str,int i);

#endif