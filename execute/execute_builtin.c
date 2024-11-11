/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akar <akar@student.42istanbul.com.tr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:11:14 by ahmeetkaar        #+#    #+#             */
/*   Updated: 2024/11/11 20:40:42 by akar             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        s1++;
        s2++;
    }
    return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int is_builtin(char *cmd)
{
    if (ft_strcmp(cmd, "cd") == 0)
        return (1);
    else if (ft_strcmp(cmd, "echo") == 0)
        return (1);
    else if (ft_strcmp(cmd, "pwd") == 0)
        return (1);
    else if (ft_strcmp(cmd, "export") == 0)
        return (1);
    else if (ft_strcmp(cmd, "unset") == 0)
        return (1);
    else if (ft_strcmp(cmd, "env") == 0)
        return (1);
    else if (ft_strcmp(cmd, "exit") == 0)
        return (1);
    return (0); 
}


void execute_builtin(char **args, t_shell *mini)
{
    
    if (ft_strcmp(args[0], "cd") == 0)
        ft_cd(args, mini);
    else if (ft_strcmp(args[0], "pwd") == 0) 
        printpwd();
    else if (ft_strcmp(args[0], "echo") == 0)
        ft_echo(args);
    else if (ft_strcmp(args[0],"export") == 0&& !args[1])
        ft_env(mini->env, 1);
    else if (ft_strcmp(args[0], "export") == 0)
        ft_export(mini, args, 1, NULL);
    else if (ft_strcmp(args[0], "unset") == 0)
       unset_env_var(args[1], mini);
    else if (ft_strcmp(args[0], "env") == 0)
        ft_env(mini->env, 0);
    else if (strcmp(args[0], "exit") == 0)
        ft_exit(args);
    else
    {
        ft_putstr_fd("minishell5: ", STDERR_FILENO);
        ft_putstr_fd(args[0], STDERR_FILENO);
        ft_putendl_fd(": command not found", STDERR_FILENO);
        g_global_exit = 127;
    }
}