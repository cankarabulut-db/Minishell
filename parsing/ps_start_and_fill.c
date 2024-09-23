/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:43:20 by nkarabul          #+#    #+#             */
/*   Updated: 2024/09/18 00:13:53 by nkarabul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void cmd_find_fill(t_shell *cmd,char *str,int i)
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


void	split_pipe_and_fill(t_shell *cmd, char *str, int i, t_rdr *listsize)
{
	char	**pipe_cmd;
	t_shell	*temp;

	pipe_cmd = ft_split(str, PIPE);
	listsize->listsize = ft_strplen(pipe_cmd);
	temp = cmd;
	while (listsize->listsize > i)
	{
		if(check_redirect(pipe_cmd[i]))
		{
			heredoc_append_control(pipe_cmd[i], 0);
			input_output_control(pipe_cmd[i], 0);
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
}


void single_cmd_fill(t_shell *cmd, char *str, t_rdr *list)
{
	char *dist_str; 

	dist_str = ft_strdup(str);
	if(check_redirect(str))
	{
		heredoc_append_control(dist_str, 0);
		input_output_control(dist_str, 0);
		redirect_find_fill(cmd, dist_str, 0, list);
	}
	cmd_find_fill(cmd, dist_str,0);
	args_find_fill(cmd, dist_str);
	make_empty(dist_str,-1);
	cmd->next = NULL;
}

void	struct_filler(t_shell *cmd, char *str, int i)
{
	t_rdr	list;

	(void)i;
	if (ft_exist(str, PIPE, 0))
			split_pipe_and_fill(cmd, str, 0, &list);
	else
			single_cmd_fill(cmd, str, &list);

	for (; cmd!= NULL;)          //REDİRECT VS YOKSA OKUMASIN !
	{
		printf("*****BEGİNNİNG*****\n");
		if(cmd->cmd)
			printf("cmd : %s\n",cmd->cmd);
		if(cmd->append)
			for (int i = 0; cmd->append[i]; i++)
				printf("Append :%s\n",cmd->append[i]);
		if(cmd->heredoc)
			for (int i = 0; cmd->heredoc[i]; i++)
				printf("heredoc : %s\n", cmd->heredoc[i]);
		if(cmd->args)
			for (int i = 0; cmd->args[i]; i++)
				printf("args : %s\n", cmd->args[i]);
		if(cmd->input)
			for (int i = 0; cmd->input[i]; i++)
				printf("input : %s\n", cmd->input[i]);
		if(cmd->output)
			for (int i = 0; cmd->output[i]; i++)
				printf("output : %s\n", cmd->output[i]);
		cmd =cmd->next;
	}
}
void	start_parse(char *org_str, t_shell *cmd)
{
	char	*tokenized_str;

	(void)cmd;
	tokenized_str = ft_strdup(org_str);
	quote_check(org_str);
	tokenize1(tokenized_str, org_str, 0);
	tokenize2(tokenized_str, org_str, 0);
	free(tokenized_str);
	pipe_ba(org_str, 0);
	struct_filler(cmd, org_str, 0);
}
