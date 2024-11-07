/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_start_and_fill.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkarabul <nkarabul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:43:20 by nkarabul          #+#    #+#             */
/*   Updated: 2024/11/07 20:20:28 by nkarabul         ###   ########.fr       */
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


int single_cmd_fill(t_shell *cmd, char *str, t_rdr *list)
{
	char *dist_str; 

	dist_str = ft_strdup(str);
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
			split_pipe_and_fill(cmd, str, 0, &list);
	else
	{
		if(single_cmd_fill(cmd, str, &list) == -1)
			return -1;
		else
			(void)single_cmd_fill(cmd, str, &list);
	}
	return (0);
}
void dollar_token(char *str,int i)
{
	while(str[i])
	{
		if(str[i] == DOUBLEQ || str[i] == SINGLEQ)
		{
			i++;
			while(str[i] != DOUBLEQ && str[i] != SINGLEQ)
			{
				if(str[i] == '$')
					str[i] = DOLLAR;
				i++;
			}
		}
		i++;
	}
}

//void dollar_finder(char *str,int i,int start)
//{
//	while(str[i])	
//	{
//		if(str[i] == DOUBLEQ || str[i] == SINGLEQ)
//		{
//			i++;
//			while(str[i] != DOUBLEQ && str[i] != SINGLEQ)
//			{
//				if(str[i] == DOLLAR)
//				{
//					i++;
//					while(str[i] != ' ' && str[i])
//						i++;
//				}
//			}
//		}
//	}
//}
void tokenize3(char *str,int i)
{
	while(str[i])
	{
		if(str[i] == '$')
			str[i] = DOLLAR;
		i++;
	}
}
int	start_parse(char *org_str, t_shell *cmd)
{
	char	*tokenized_str;

	(void)cmd;
	
	tokenized_str = ft_strdup(org_str);
	if(quote_check(org_str) == -1)
		return -1;
	tokenize1(tokenized_str, org_str, 0);
	tokenize2(tokenized_str, org_str, 0);
	org_str = set_dolar(org_str, cmd); //set_dolar leaks org_str leaks
	printf("%s\n",org_str);
	free(tokenized_str);
	if(pipe_ba(org_str, 0) == -1)
		return (-1);
	if(struct_filler(cmd, org_str, 0) == -1)
		return (-1);
	else
		(void)struct_filler(cmd, org_str, 0);
	return (0);
}
