/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:35:09 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/07 19:20:46 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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

#define CHAR 1
#define DOUBLEQ 2
#define SINGLEQ 3
#define HEREDOC 4 // <<
#define APPEND 5 // >>
#define OUTPUT 6 // >
#define INPUT 7 // <
#define PIPE 8

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
	struct s_env *main_env;
	struct s_shell *next;
}	t_shell;

typedef struct s_rdr
{
	int	ic;
	int oc;
	int ac;
	int hc;
	int icwhile;
	int ocwhile;
	int acwhile;
	int hcwhile;
}	t_rdr;

typedef struct s_garbage{
	void *data;
	struct s_garbage *next;
}				t_garbage;

typedef struct s_env
{
	char **env;
}			t_env;

			


void error_msg(char *str1,int i);
void start_parse(char *org_str,t_shell *cmd);
void split_pipe(t_shell *cmd,char *str,int i, int size);
void start_cmd(char **str);
void struct_initializer(t_shell *cmd);
void struct_filler(t_shell *cmd, char *str, int i);
int ft_exist(char *str,char a,int i);
void cmd_filler(t_shell *cmd,char *str,int i,int b);
void tokenize1(char *str,char *org_str,int i);
void tokenize2(char *str,char *org_str,int i);
int ft_strplen(char **str);
char *quote_remover(char *str,int i,int j);
void quote_check(char *str);
void pipe_redirect_ba(char *str,int i);
void redirect_finder(t_shell *cmd,char *str,int i,int type);
void redirects_filler(t_shell *cmd,char *str,int type,int i);

#endif