/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmeetkaar <ahmeetkaar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:14:41 by akar              #+#    #+#             */
/*   Updated: 2024/11/20 20:27:57 by ahmeetkaar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc2(t_shell *shell, int fd[2], int fd_2[2])
{
	char	*heredoc;
	int		i;

	i = 0;
	shell->hpid = fork();
	if (shell->hpid == 0)
	{
		set_signal(HEREDOC_P);
		dup2(fd_2[0], 0);
		dup2(fd_2[1], 1);
		while (shell->heredoc[i])
		{
			heredoc = readline("> ");
			if (g_global_exit == 999)
			{
				free(heredoc);
				break ;
			}
			if (!shell->heredoc[i + 1] && !check_if_same(shell->heredoc[i],
					heredoc))
				ft_putendl_fd(heredoc, fd[1]);
			if (check_if_same(shell->heredoc[i], heredoc))
			{
				i++;
			}
			free(heredoc);
		}
		exit(0);
	}
	return (0);
}

void	heredoc_init(t_shell *shell, int fd_2[2])
{
	int	fd[2];
	int	status;

	pipe(fd);
	if (shell->heredoc && shell->heredoc[0])
		handle_heredoc2(shell, fd, fd_2);
	close(fd[1]);
	dup2(fd[0], 0);
	close(fd[0]);
	waitpid(shell->hpid, &status, 0);
}
