/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_start_and_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:43:20 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/11 21:48:31 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void cmd_find_fill(t_shell *cmd,char *str,int i) // burda skntı var ls | wc -l
{
	int start;

	while(str[i] == ' ')
		i++;
	start = i;
	while(str[i] != ' ' && str[i])
		i++;
	if(!ft_print_s(str[i]) && !ft_print_s(start))
	{
		cmd->cmd = quote_remover(ft_substr(str,start,i - start), 0, 0);
		empty_maker(str,' ',start,i - start);
	}
}


int	split_pipe_and_fill(t_shell *cmd, char *str, int i, t_rdr *listsize)
{
	char	**pipe_cmd;
	t_shell	*temp;
	
	pipe_cmd = ft_split(str, PIPE);
	listsize->listsize = ft_strplen(pipe_cmd);
	temp = cmd;
	while (listsize->listsize > i)
	{
		cmd->org_rdr = ft_strdup(pipe_cmd[i]);
		if(check_redirect(pipe_cmd[i]))
		{
			if(heredoc_append_control(pipe_cmd[i], 0) || input_output_control(pipe_cmd[i], 0) )
				return (-1);
			redirect_find_fill(cmd, pipe_cmd[i], 0, listsize);
		}
		cmd_find_fill(cmd,pipe_cmd[i],0);
		args_find_fill(cmd, pipe_cmd[i]);
		make_empty(pipe_cmd[i],-1);
		if(i == listsize->listsize -1)
		{
			cmd->next = NULL;
			break;
		}
		cmd->next = malloc(sizeof(t_shell));
		cmd = cmd->next;
		i++;
	}
	cmd = temp;
	return (0);
}


int single_cmd_fill(t_shell *cmd, char *str, t_rdr *list)
{
	char *dist_str; 

	dist_str = ft_strdup(str);
	cmd->org_rdr = ft_strdup(dist_str);
	if(check_redirect(str))
	{
		if(heredoc_append_control(dist_str, 0) == -1)
			return (-1);
		if(input_output_control(dist_str, 0) == -1)
			return (-1);
		redirect_find_fill(cmd, dist_str, 0, list);
	}
	cmd_find_fill(cmd, dist_str,0);
	args_find_fill(cmd, dist_str);
	make_empty(dist_str,-1);
	cmd->next = NULL;
	return (0);
}

int	struct_filler(t_shell *cmd, char *str, int i)
{
	t_rdr	list;

	(void)i;
	if (ft_exist(str, PIPE, 0))
	{
		if(split_pipe_and_fill(cmd, str, 0, &list) == -1)
			return (-1);
	}
	else
	{
		if(single_cmd_fill(cmd, str, &list) == -1)
			return (-1);
	}
	return (0);
}
int	start_parse(char *org_str, t_shell *cmd)
{
	char	*tokenized_str;
	
	tokenized_str = ft_strdup(org_str);
	if(quote_check(org_str) == -1)
		return -1;
	tokenize1(tokenized_str, org_str, 0);
	tokenize2(tokenized_str, org_str, 0);
	org_str = set_dolar(org_str, cmd,0,0); //set_dolar leaks org_str leaks
	free(tokenized_str);
	if (org_str == NULL)
		return (-1);
	if(pipe_ba(org_str, 0) == -1)
		return (-1);
	if(struct_filler(cmd, org_str, 0) == 0) // ls | wc hatası
	{
		sleep(10000);
		return (0);
	}
	else
	{
		if (cmd->cmd)
			free(cmd->cmd);
		
			
		return (-1);
	}
}
