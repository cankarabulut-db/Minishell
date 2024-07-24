/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:35:09 by nkarabul          #+#    #+#             */
/*   Updated: 2024/07/24 19:26:11 by nkarabul         ###   ########.fr       */
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
	struct s_main *next;
}	t_shell;

typedef struct s_garbage{
	void *data;
	struct s_garbage *next;
}				t_garbage;

typedef struct s_env
{
	char **env;
}			t_env;

			


void error_msg(char *str);
void start_parse(char *str);
void start_cmd(char **str);

#endif