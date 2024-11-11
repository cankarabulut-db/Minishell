/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmeetkaar <ahmeetkaar@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 17:35:41 by akar              #+#    #+#             */
/*   Updated: 2024/11/10 17:08:50 by ahmeetkaar       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	flag_control(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	echo_flag_control(char **arg, int *i)
{
	if (flag_control(arg[*i] + 1) == 1)
		return ;
	*i += 1;
	if (arg[*i] && arg[*i][0] == '-')
		echo_flag_control(arg, i);
}

void	echo_with_arg(char **arg)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (arg[i] && arg[i][0] == '-')
		echo_flag_control(arg, &i);
	flag = i;
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 1 && arg[flag])
		ft_putstr_fd("\n", 1);
}

void	ft_echo(char **arg)
{
	if (arg && arg[1])
	{
		echo_with_arg(arg);
	}
	else
		printf("\n");
	g_global_exit = 0;
}
