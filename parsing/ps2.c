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
void redirect_size(t_rdr *rdrc, char *str)
{
	rdrc->ic = redirect_counter(str, 0, INPUT);
	rdrc->oc = redirect_counter(str, 0, OUTPUT);
	rdrc->ac = redirect_counter(str, 0, APPEND);
	rdrc->hc = redirect_counter(str, 0, HEREDOC);
}

void	redirect_malloc(t_shell *cmd, char *str, t_rdr *rdrc)
{
	redirect_size(rdrc, str);
	if(rdrc->ic > 0)
	{
		cmd->input = malloc(sizeof(char *) * rdrc->ic + 1);
		if(!cmd->input)
			error_msg(str,14);
	}
	if(rdrc->oc > 0)
	{
		cmd->output = malloc(sizeof(char *) * rdrc->oc + 1);
		if(!cmd->output)
			error_msg(str,14);
	}
	if(rdrc->hc > 0)
	{
		cmd->heredoc = malloc(sizeof(char *) * rdrc->hc + 1);
		if(!cmd->heredoc)
			error_msg(str,14);
	}
	if(rdrc->ac > 0)
	{
		cmd->append = malloc(sizeof(char *) * rdrc->ac + 1);
		if(!cmd->append)
			error_msg(str,14);
	}
}

void redirect_fill_null(t_shell *cmd,t_rdr *rc)
{
	if(cmd->append)
		cmd->append[rc->ac] = NULL;
	if(cmd->heredoc)
		cmd->heredoc[rc->hc] = NULL;
	if(cmd->input)
		cmd->input[rc->ic] = NULL;
	if(cmd->output)
		cmd->output[rc->oc] = NULL;
}

void	redirect_find_fill(t_shell *cmd, char *str, int i, t_rdr *rdrcount)
{
	rdr_makezero(rdrcount);
	redirect_malloc(cmd, str, rdrcount);
	redirect_fill_null(cmd,rdrcount);
	while (str[i])
	{
		if (str[i] == INPUT || str[i] == OUTPUT || \
			str[i] == APPEND || str[i] == HEREDOC)
		{
			rdrcount->type = str[i];
			if (rdrcount->type == APPEND || rdrcount->type == HEREDOC)
			{
				str[i] = ' ';
				str[i + 1] = ' ';
				i += 2;
			}
			else if(rdrcount->type == INPUT || rdrcount->type == OUTPUT)
				str[i++] = ' ';
			while (str[i] == ' ')
				i++;
			redirects_filler(cmd, str, rdrcount, i);
		}
		i++;
	}
}

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

int check_redirect(char *pipe_cmd)
{
	int	i;

	i = -1;
	while (pipe_cmd[++i])
		if (pipe_cmd[i] == HEREDOC || pipe_cmd[i] == OUTPUT || \
		pipe_cmd[i] == INPUT || pipe_cmd[i] == APPEND)
			return (1);
	return (0);
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
	args_find_fill(cmd, str);
	make_empty(dist_str,-1);
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
			printf("var\n");
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
